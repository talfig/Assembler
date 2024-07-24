#ifndef ERRORS_H
#define ERRORS_H

#include "macr.h"

int allocFail(const char *ptr, macr_table *tb, FILE *fp);

int openFail(FILE *fp);

#endif /* ERRORS_H */
