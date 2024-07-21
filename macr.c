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
    if(!tmp) setHead(tb, ptr);
    else setNext(tmp, ptr); /* Otherwise, add the new node at the end of the list */
}


void freeTable(macr_table *tb) {
    macr *ptr, *tmp;

    ptr = getHead(tb);
    while(ptr) {
        tmp = ptr;
        ptr = getNext(ptr);
        if(tmp->name)
            free(tmp->name);
        if(tmp->info)
            free(tmp->info);
        free(tmp);
    }
}

char *my_strdup(const char *s) {
    char *d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

void save_macr(macr_table *tb, char *str, FILE *fp, FILE *fptr) {
    char *info, *tmp, ptr[ROW_SIZE + 1];
    int len = 0;
    macr *mcr = malloc(sizeof(macr));
    if(!mcr) {
        fprintf(stderr, "Memory allocation failed!\n");
        freeTable(tb);
        fclose(fp);
        fclose(fptr);
        exit(EXIT_FAILURE);
    }
    setNext(mcr, NULL);
    setName(mcr, my_strdup(str));
    addToTable(tb, mcr);
    allocFail(getName(mcr), tb, fp, fptr);
    info = malloc(0);
    allocFail(info, tb, fp, fptr);
    while((tmp = fgets(ptr, ROW_SIZE, fp))) {
        nextToken(str, &tmp);
        if(!strcmp(str, "endmacr"))
            break;
        tmp = realloc(info, len + ROW_SIZE + 1);
        if(!tmp) {
            fprintf(stderr, "Memory reallocation failed!\n");
            free(info);
            freeTable(tb);
            fclose(fp);
            fclose(fptr);
            exit(EXIT_FAILURE);
        }
        info = tmp;
        tmp += len;
        strcpy(tmp, ptr);
        len = strlen(info);
    }
    setInfo(mcr, info);
}
