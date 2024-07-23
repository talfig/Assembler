#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "errors.h"
#include "preprocessor.h"
#include "token_utils.h"

/* macr_table */

void emptyMacrTable(macr_table *tb) {
    tb->head = NULL;
}

macr *getMacrTail(macr_table *tb) {
    macr *ptr = tb->head;

    if(!ptr) return NULL;

    /* Traverse the list to find the tail macr */
    while(ptr -> next) ptr = ptr -> next;
    return ptr;
}

void addToMacrTable(macr_table *tb, macr *ptr) {
    macr *tmp = getMacrTail(tb);

    /* If the bucket is empty, set the new node as the head */
    if(!tmp) tb->head = ptr;
    else tmp->next = ptr; /* Otherwise, add the new node at the end of the list */
}

void freeMacrTable(macr_table *tb) {
    macr *ptr, *tmp;

    ptr = tb->head;
    while(ptr) {
        tmp = ptr;
        ptr = ptr->next;
        if(tmp->name)
            free(tmp->name);
        if(tmp->info)
            free(tmp->info);
        free(tmp);
    }
}

macr *find_macr(macr_table *tb, char *str) {
    macr *ptr = tb->head;
    while(ptr) {
        if(!strcmp(str, ptr->name))
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *res = malloc(len + 1);
    if(!res) return NULL;
    strcpy(res, s);
    return res;
}

void save_macr(macr_table *tb, char *str, FILE *fp, FILE *fptr) {
    char *info, *new_info, *tmp, ptr[ROW_SIZE + 1];
    unsigned long len = 0;
    macr *mcr = malloc(sizeof(macr));
    if(!mcr) {
        fprintf(stderr, "Memory allocation failed!\n");
        freeMacrTable(tb);
        fclose(fp);
        fclose(fptr);
        exit(EXIT_FAILURE);
    }
    mcr->next = NULL;
    mcr->name = my_strdup(str);
    addToMacrTable(tb, mcr);
    allocFail(mcr->name, tb, fp, fptr);
    info = malloc(0);
    allocFail(info, tb, fp, fptr);
    while((tmp = fgets(ptr, ROW_SIZE, fp))) {
        nextToken(str, &tmp);
        if(!strcmp(str, "endmacr"))
            break;
        new_info = realloc(info, len + ROW_SIZE + 1);
        if(!new_info) {
            fprintf(stderr, "Memory reallocation failed!\n");
            free(info);
            freeMacrTable(tb);
            fclose(fp);
            fclose(fptr);
            exit(EXIT_FAILURE);
        }
        info = new_info;
        tmp = info + len;
        strcpy(tmp, ptr);
        len = strlen(info);
    }
    mcr->info = info;
}
