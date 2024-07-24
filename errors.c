#include <stdio.h>
#include "macr.h"

int allocFail(const char *ptr, macr_table *tb, FILE *fp) { /* Add file closer */
    if(!ptr) {
        fprintf(stderr, "Memory allocation failed for name!\n");
        freeMacrTable(tb);
        fclose(fp);
        return 1;
    }
    return 0;
}

int openFail(FILE *fp) {
    if(!fp) {
        fprintf(stderr, "Unable to open the file!\n");
        return 1;
    }
    return 0;
}

