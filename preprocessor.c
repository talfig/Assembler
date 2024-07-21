#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "errors.h"
#include "preprocessor.h"
#include "token_utils.h"

FILE *preprocess(FILE *fp) {
    char ptr[ROW_SIZE + 1], str[LABEL_SIZE + 1], *tmp;
    FILE *fptr;
    macr *mcr;
    macr_table tb;
    emptyTable(&tb);
    fptr = fopen("out.txt", "w");
    openFail(fptr);
    while((tmp = fgets(ptr, ROW_SIZE, fp))) {
        nextToken(str, &tmp);
        mcr = find_macr(&tb, str);
        if(mcr)
            fprintf(fptr, "%s", getInfo(mcr));
        else if(strcmp(str, "macr"))
            fprintf(fptr, "%s", ptr);
        else {
            nextToken(str, &tmp);
            save_macr(&tb, str, fp, fptr);
        }
    }
    freeTable(&tb);
    fclose(fp);
    return fptr;
}