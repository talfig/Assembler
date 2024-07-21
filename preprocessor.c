#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "errors.h"
#include "preprocessor.h"
#include "token_utils.h"

FILE *preprocess(FILE *fp) {
    char *ptr, *str, *tmp;
    FILE *fptr;
    macr *mcr;
    macr_table tb;
    emptyTable(&tb);
    fptr = fopen("out.txt", "w");
    openFail(fptr);
    ptr = malloc(ROW_SIZE + 1);
    allocFail(ptr);
    str = malloc(LABEL_SIZE + 1);
    allocFail(str);
    while((tmp = fgets(ptr, ROW_SIZE, fp))) {
        nextToken(str, &tmp);
        mcr = find_macr(&tb, str);
        if(mcr)
            fprintf(fptr, "%s", getInfo(mcr));
        else if(strcmp(str, "macr"))
            fprintf(fptr, "%s", ptr);
        else {
            nextToken(str, &tmp);
            save_macr(&tb, str, fp);
        }
    }
    free(str);
    free(ptr);
    freeTable(&tb);
    fclose(fp);
    return fptr;
}