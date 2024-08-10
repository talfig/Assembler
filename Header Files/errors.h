#ifndef ERRORS_H
#define ERRORS_H

#include "macr.h"
#include "label.h"
#include "globals.h"

const char *getError(int error_code);

void allocFail(const char *ptr, macr_table *tb, FILE *fp_in, FILE *fp_out);

void openFail(FILE *fp);

int checkLines(char *file_name);

int isLegalOpcode(opcode op, char *ptr, short *iptr, int line_counter, label_table *label_tb, macr_table *macr_tb);

int isLegalData(char *ptr, short *dptr, short idx, int line_counter);

int isLegalString(char *ptr, short *dptr, short idx, int line_counter);

#endif /* ERRORS_H */
