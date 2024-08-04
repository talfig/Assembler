#ifndef ERRORS_H
#define ERRORS_H

#include "macr.h"

const char *getError(int error_code);

void allocFail(const char *ptr, macr_table *tb, FILE *fp, FILE *fptr);

void openFail(FILE *fp);

int checkLines(char *file_name);

#endif /* ERRORS_H */
