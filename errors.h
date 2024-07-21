#ifndef ERRORS_H
#define ERRORS_H

void allocFail(char *ptr, macr_table *tb, FILE *fp, FILE *fptr);

void reallocFail(char *ptr, char *tmp);

void openFail(FILE *fp);

#endif /* ERRORS_H */
