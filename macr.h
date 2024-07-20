#ifndef MACR_H
#define MACR_H

typedef struct macr {
    char *name;
    char *info;
    struct macr *next;
} macr;

char *getName(macr *node);

char *getInfo(macr *node);

macr *getNext(macr *node);

void setName(macr *node, char *name);

void setInfo(macr *node, char *info);

void setNext(macr *node, macr *next);

typedef struct {
    macr *head;
} macr_table;

void emptyTable(macr_table *tb);

macr *getHead(macr_table *tb);

void setHead(macr_table *tb, macr *head);

macr *getTail(macr_table *tb);

void addToTable(macr_table *tb, macr *ptr);

void freeTable(macr_table *tb);

macr *find_macr(macr_table *tb, char *str);

void save_macr(macr_table *tb, char *str, FILE *fp);

#endif /* MACR */
