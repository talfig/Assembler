#ifndef ERRORS_H
#define ERRORS_H

#include "macr.h"

void allocFail(const char *ptr, macr_table *tb, FILE *fp, FILE *fptr);

void openFail(FILE *fp);

#endif /* ERRORS_H */
