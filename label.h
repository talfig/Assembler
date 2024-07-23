#ifndef LABEL_H
#define LABEL_H

int isLabel(char *str);

typedef struct label{
    int line;
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

label *find_label(label_table *tb, char *str);

#endif /* LABEL_H */
