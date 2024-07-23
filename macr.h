#ifndef MACR_H
#define MACR_H

typedef struct macr {
    char *name;
    char *info;
    struct macr *next;
} macr;

typedef struct {
    macr *head;
} macr_table;

void emptyMacrTable(macr_table *tb);

macr *getMacrTail(macr_table *tb);

void addToMacrTable(macr_table *tb, macr *ptr);

void freeMacrTable(macr_table *tb);

macr *find_macr(macr_table *tb, char *str);

void save_macr(macr_table *tb, char *str, FILE *fp, FILE *fptr);

#endif /* MACR */
