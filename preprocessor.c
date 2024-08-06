#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "errors.h"

int preprocess(FILE *fp) {
    char line[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 1], name[MAX_LABEL_SIZE + 1], *tmp;
    int foundErr = EXIT_SUCCESS, exit_code;
    FILE *fptr;
    macr *mcr;
    macr_table macr_tb;
    emptyMacrTable(&macr_tb);

    if(checkLines("test.txt"))
        foundErr = EXIT_FAILURE;

    fptr = fopen("out.txt", "w");
    if(!fptr) {
        fprintf(stderr, "Unable to open the file!\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    while((tmp = fgets(line, MAX_LINE_SIZE + 1, fp))) {
        nextToken(str, &tmp, ' ');
        nextToken(name, &tmp, ' ');
        mcr = find_macr(&macr_tb, str);

        if(mcr) {
            if(*name) {
                fprintf(stderr, "Line must contain only the macro name!\n");
                foundErr = EXIT_FAILURE;
                continue;
            }
            fprintf(fptr, "%s", mcr->info);
        }

        else if(strcmp(str, "macr")) {
            if(!strstr(tmp, "macr"))
                fprintf(fptr, "%s", line);
            else {
                fprintf(stderr, "Line must contain only a macro definition!\n");
                foundErr = EXIT_FAILURE;
                continue;
            }

        }

        else {
            nextToken(str, &tmp, ' ');
            if(*str || !(*name)) {
                fprintf(stderr, "Line must contain only a macro definition!\n");
                foundErr = EXIT_FAILURE;
                continue;
            }

            if(isLegalMacrName(&macr_tb, name)) {
                exit_code = save_macr(&macr_tb, name, fp, fptr);
                if(exit_code) return exit_code;
            } else {
                fprintf(stderr, "Invalid macro name!\n");
                foundErr = EXIT_FAILURE;
                continue;
            }
        }
    }

    freeMacrTable(&macr_tb);
    fclose(fp);
    fclose(fptr);
    return foundErr;
}
