#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "preprocessor.h"

int checkLines(char *file_name) {
    FILE *fp;
    char line[MAX_LINE_SIZE + 2], last;
    int foundErr = 0;

    /* Open the file in read mode */
    fp = fopen(file_name, "r");
    if(!fp) {
        fprintf(stderr, "Unable to open the file!\n");
        return EXIT_FAILURE;
    }

    /* Read each line of the file */
    while(fgets(line, MAX_LINE_SIZE + 2, fp)) {
        if(strlen(line) > MAX_LINE_SIZE) {
            foundErr = 1;
            break;
        }
    }
    if(foundErr)
        fprintf(stderr, "Found line that exceeds %d characters!\n", MAX_LINE_SIZE);

    /* Close the file */
    fclose(fp);

    return EXIT_SUCCESS;
}

void allocFail(const char *ptr, macr_table *tb, FILE *fp, FILE *fptr) { /* Add file closer */
    if(!ptr) {
        fprintf(stderr, "Memory allocation failed for name!\n");
        freeMacrTable(tb);
        fclose(fp);
        fclose(fptr);
        exit(EXIT_FAILURE);
    }
}

void openFail(FILE *fp) {
    if(!fp) {
        fprintf(stderr, "Unable to open the file!\n");
        exit(EXIT_FAILURE);
    }
}

