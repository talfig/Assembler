#include <stdlib.h>
#include <string.h>
#include "label.h"

int isLabel(char *str) {
    return  (strlen(str) <= 31) &&
            ('a' <= str[0] && str[0] <= 'z' ||
            'A' <= str[0] && str[0] <= 'Z');
}

/* label_table */

void emptyLabelTable(label_table *tb) {
    tb->head = NULL;
}

label *getLabelTail(label_table *tb) {
    label *ptr = tb->head;

    if(!ptr) return NULL;

    /* Traverse the list to find the tail macr */
    while(ptr->next) ptr = ptr->next;
    return ptr;
}

void addToLabelTable(label_table *tb, label *ptr) {
    label *tmp = getLabelTail(tb);

    /* If the bucket is empty, set the new node as the head */
    if(!tmp) tb->head = ptr;
    else tmp->next = ptr; /* Otherwise, add the new node at the end of the list */
}


void freeLabelTable(label_table *tb) {
    label *ptr, *tmp;

    ptr = tb->head;
    while(ptr) {
        tmp = ptr;
        ptr = ptr->next;
        if(tmp->name)
            free(tmp->name);
        free(tmp);
    }
}

label *find_label(label_table *tb, char *str) {
    label *ptr = tb->head;
    while(ptr) {
        if(!strcmp(str, ptr->name))
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}