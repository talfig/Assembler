#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "preprocessor.h"
#include "token_utils.h"

int first_pass(FILE *fp) {
    char ptr[MAX_ROW_SIZE + 1], str[MAX_LABEL_SIZE + 1], name[MAX_LABEL_SIZE + 1], *tmp;
    int foundErr = 0, exit_code;
    FILE *fptr;
    macr *mcr;
    macr_table macr_tb;

    emptyMacrTable(&macr_tb);
    fptr = fopen("out.txt", "w");
    if(!fptr) {
        fprintf(stderr, "Unable to open the file!\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    while((tmp = fgets(ptr, MAX_ROW_SIZE + 1, fp))) {
        nextToken(str, &tmp, ' ');
        mcr = find_macr(&macr_tb, str);

        if(mcr)
            fprintf(fptr, "%s", mcr->info);

        else if(strcmp(str, "macr")) {
            if(!strstr(tmp, "macr"))
                fprintf(fptr, "%s", ptr);
            else {
                fprintf(stderr, "Line must contain only a macro definition!\n");
                return EXIT_FAILURE;
            }

        }

        else {
            nextToken(name, &tmp, ' ');
            nextToken(str, &tmp, ' ');
            if(*str || !(*name)) {
                fprintf(stderr, "Line must contain only a macro definition!\n");
                return EXIT_FAILURE;
            }

            if(isLegalMacrName(&macr_tb, name)) {
                exit_code = save_macr(&macr_tb, name, fp, fptr);
                if(exit_code) return exit_code;
            } else {
                fprintf(stderr, "Invalid macro name!\n");
                foundErr = EXIT_FAILURE;
                break;
            }
        }
    }

    freeMacrTable(&macr_tb);
    fclose(fp);
    fclose(fptr);
    return foundErr;
}

