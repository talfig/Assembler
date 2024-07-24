#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "errors.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "label.h"

int preprocess(FILE *fp) {
    char ptr[ROW_SIZE + 1], str[LABEL_SIZE + 1], name[LABEL_SIZE + 1], *tmp;
    int foundErr = 0, exit_code;
    FILE *fptr;
    macr *mcr;
    label_table label_tb;
    macr_table macr_tb;

    emptyLabelTable(&label_tb);
    emptyMacrTable(&macr_tb);
    fptr = fopen("out.txt", "w");
    if(openFail(fptr)) {
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    while((tmp = fgets(ptr, ROW_SIZE + 1, fp))) {
        nextToken(str, LABEL_SIZE + 1, &tmp);
        mcr = find_macr(&macr_tb, str);
        if(mcr)
            fprintf(fptr, "%s", mcr->info);
        else if(strcmp(str, "macr"))
            fprintf(fptr, "%s", ptr);

        else {
            nextToken(name, LABEL_SIZE + 1, &tmp);
            nextToken(str, LABEL_SIZE + 1, &tmp);
            if(*str) {
                fprintf(stderr, "Line must contain only a macro definition!\n");
                return 1;
            }

            if(isLegalName(&label_tb, &macr_tb, name)) {
                exit_code = save_macr(&macr_tb, name, fp);
                if(exit_code) {
                    fclose(fptr);
                    freeLabelTable(&label_tb); /* macr_tb is already freed */
                    if(exit_code == 1) exit(EXIT_FAILURE);
                    else return 1;
                }
            } else {
                foundErr = 1;
                break;
            }
        }
    }

    freeLabelTable(&label_tb);
    freeMacrTable(&macr_tb);
    fclose(fp);
    fclose(fptr);
    return foundErr;
}
