#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "errors.h"
#include "preprocessor.h"
#include "token_utils.h"

char *getName(macr *mcr) {
    return mcr->name;
}

char *getInfo(macr *mcr) {
    return mcr->info;
}

macr *getNext(macr *mcr) {
    return mcr->next;
}

void setName(macr *mcr, char *name) {
    mcr->name = name;
}

void setInfo(macr *mcr, char *info) {
    mcr->info = info;
}

void setNext(macr *mcr, macr *next) {
    mcr->next = next;
}

/* macr_table */

void emptyTable(macr_table *tb) {
    tb->head = NULL;
}

macr *getHead(macr_table *tb) {
    return tb->head;
}

void setHead(macr_table *tb, macr *head) {
    tb->head = head;
}

macr *find_macr(macr_table *tb, char *str) {
    macr *ptr = getHead(tb);
    while(ptr) {
        if(!strcmp(getName(ptr), str))
            return ptr;
        ptr = getNext(ptr);
    }
    return NULL;
}


macr *getTail(macr_table *tb) {
    macr *ptr = getHead(tb);

    if(!ptr) return NULL;

    /* Traverse the list to find the tail macr */
    while(getNext(ptr)) ptr = getNext(ptr);
    return ptr;
}


void addToTable(macr_table *tb, macr *ptr) {
    macr *tmp = getTail(tb);

    /* If the bucket is empty, set the new node as the head */
    if(!tmp) tb->head = ptr;
    else setNext(tmp, ptr); /* Otherwise, add the new node at the end of the list */
}


void freeTable(macr_table *tb) {
    macr *ptr, *tmp;

    ptr = getHead(tb);
    while(ptr) {
        tmp = ptr;
        ptr = getNext(ptr);
        free(tmp->name);
        free(tmp->info);
        free(tmp);
    }
}

void save_macr(macr_table *tb, char *str, FILE *fp) {
    char *info, *ptr, *tmp;
    size_t size = ROW_SIZE + 1;
    macr *mcr = malloc(sizeof(macr));
    if(!mcr) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    setName(mcr, str);
    info = malloc(size);
    allocFail(info);
    ptr = malloc(size);
    allocFail(ptr);
    do {
        tmp = fgets(ptr, ROW_SIZE, fp);
        nextToken(str, &tmp);
        if(!strcmp(str, "endmacr"))
            break;
        tmp = realloc(info, size);
        if(!tmp) {
            fprintf(stderr, "Memory reallocation failed!\n");
            free(info);
            free(ptr);
            exit(EXIT_FAILURE);
        }
        tmp += size - ROW_SIZE - 1;
        strcpy(tmp, ptr);
        size += ROW_SIZE;
    } while(1);
    setInfo(mcr, info);
    addToTable(tb, mcr);
    free(ptr);
}
