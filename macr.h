#ifndef MACR_H
#define MACR_H

#include "stdio.h"

#define MACR_DEF_ERR 1

int isLegalName(char *name);

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

macr *find_macr(macr_table *tb, char *name);

int isLegalMacrName(macr_table *macr_tb, char *name);

int save_macr(macr_table *tb, char *name, FILE *fp, FILE *fptr);

#endif /* MACR_H */
