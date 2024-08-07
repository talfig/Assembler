#ifndef ERRORS_H
#define ERRORS_H

#include "macr.h"
#include "label.h"
#include "globals.h"

const char *getError(int error_code);

void allocFail(const char *ptr, macr_table *tb, FILE *fp, FILE *fptr);

void openFail(FILE *fp);

int checkLines(char *file_name);

int isLegalOpcode(opcode op, char *ptr, label_table *label_tb, macr_table *macr_tb);

int isLegalData(char *ptr);

int isLegalString(char *ptr);

#endif /* ERRORS_H */
