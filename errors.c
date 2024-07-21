#include <stdio.h>
#include <stdlib.h>
#include "macr.h"

void allocFail(char *ptr, macr_table *tb, FILE *fp, FILE *fptr) { /* Add file closer */
    if(!ptr) {
        fprintf(stderr, "Memory allocation failed for name!\n");
        freeTable(tb);
        fclose(fp);
        fclose(fptr);
        exit(EXIT_FAILURE);
    }
}

void openFail(FILE *fp) {
    if (!fp) {
        fprintf(stderr, "Unable to open the file!\n");
        exit(EXIT_FAILURE);
    }
}

