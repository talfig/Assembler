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
    while(ptr -> next) ptr = ptr->next;
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

macr *find_macr(macr_table *tb, char *name) {
    macr *ptr = tb->head;
    while(ptr) {
        if(!strcmp(name, ptr->name))
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

int save_macr(macr_table *tb, char *name, FILE *fp) {
    char *info, *new_info, *tmp, ptr[ROW_SIZE + 1], str[LABEL_SIZE + 1];
    unsigned long len = 0;
    macr *mcr = malloc(sizeof(macr));
    if(!mcr) {
        fprintf(stderr, "Memory allocation failed!\n");
        freeMacrTable(tb);
        fclose(fp);
        return 1;
    }

    mcr->next = NULL;
    mcr->name = my_strdup(name);
    addToMacrTable(tb, mcr);
    if(allocFail(mcr->name, tb, fp)) return 1;

    info = malloc(0);
    if(allocFail(info, tb, fp)) return 1;

    while((tmp = fgets(ptr, ROW_SIZE + 1, fp))) {
        nextToken(name, LABEL_SIZE + 1, &tmp);
        nextToken(str, LABEL_SIZE + 1, &tmp);
        if(!strcmp(name, "endmacr")) {
            if(*str) {
                fprintf(stderr, "Line must contain only a macro definition!\n");
                return -1;
            }
            break;
        }

        new_info = realloc(info, len + ROW_SIZE + 1);
        if(!new_info) {
            fprintf(stderr, "Memory reallocation failed!\n");
            free(info);
            freeMacrTable(tb);
            fclose(fp);
            return 1;
        }
        info = new_info;
        tmp = info + len;
        strcpy(tmp, ptr);
        len = strlen(info);
    }
    mcr->info = info;
    return 0;
}
