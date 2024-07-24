#ifndef LABEL_H
#define LABEL_H

#include "macr.h"

int isLabel(char *str);

typedef struct label{
    int address;
    char *name;
    int isdata;
    struct label *next;
} label;

typedef struct {
    label *head;
} label_table;

void emptyLabelTable(label_table *tb);

label *getLabelTail(label_table *tb);

void addToLabelTable(label_table *tb, label *ptr);

void freeLabelTable(label_table *tb);

label *find_label(label_table *tb, char *name);

int isLegalName(label_table *label_tb, macr_table *macr_tb, char *name);

#endif /* LABEL_H */
