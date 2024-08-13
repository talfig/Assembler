#ifndef LABEL_H
#define LABEL_H

#include "macr.h"
#include "globals.h"

typedef struct label {
    int address;
    char *name;
    int is_data;
    int is_extern;
    int is_entry;
    struct label *next;
} label;

typedef struct {
    label *head;
} label_table;

void emptyLabelTable(label_table *tb);

label *getLabelTail(label_table *tb);

void addToLabelTable(label_table *tb, label *ptr);

void increaseDataLabelTableAddress(label_table *tb, int num);

void freeLabelTable(label_table *tb);

label *find_label(label_table *tb, char *name);

int isLegalLabelName(label_table *label_tb, macr_table *macr_tb, char *name);

int parseLabel(label_table *label_tb, macr_table *macr_tb, char *str, FILE *fp);

int has_entry_label(label_table *label_tb);

int has_extern_label(label_table *label_tb);

#endif /* LABEL_H */
