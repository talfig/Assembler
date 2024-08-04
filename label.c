#include <stdlib.h>
#include <string.h>
#include "label.h"
#include "macr.h"
#include "globals.h"

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

label *find_label(label_table *tb, char *name) {
    label *ptr = tb->head;
    while(ptr) {
        if(!strcmp(name, ptr->name))
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

/* add the macro */
int isLegalLabelName(label_table *label_tb, char *name) {
    opcode op = get_opcode(name);
    regis rg = get_register(name);
    instruction inst = get_instruction(name);
    label *lb = find_label(label_tb, name);
    return  isLegalName(name) &&
            strcmp(name, "macr") &&
            strcmp(name, "endmacr") &&
            (op == opcode_none) &&
            (rg == regis_none) &&
            (inst == INSTRUCTION_NONE) &&
            (lb == NULL);
}
