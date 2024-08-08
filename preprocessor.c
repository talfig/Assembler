#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "errors.h"

int preprocess(FILE *fp) {
    char line[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 2], name[MAX_LABEL_SIZE + 2], *ptr;
    int foundErr = EXIT_SUCCESS, line_counter = 0, exit_code;
    FILE *fptr;
    macr *mcr;
    macr_table tb;
    emptyMacrTable(&tb);

    if(checkLines("test.txt"))
        foundErr = EXIT_FAILURE;

    fptr = fopen("out.txt", "w");
    if(!fptr) {
        fprintf(stderr, "Unable to open the file!\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    while((ptr = fgets(line, MAX_LINE_SIZE + 1, fp))) {
        line_counter++;
        nextToken(str, &ptr, ' ');
        nextToken(name, &ptr, ' ');
        mcr = find_macr(&tb, str);

        if(mcr) {
            if(*name) {
                printf("Line must contain only the macro name!\n");
                foundErr = EXIT_FAILURE;
                continue;
            }
            fprintf(fptr, "%s", mcr->info);
        }

        else if(strcmp(str, "macr")) {
            if(!strstr(ptr, "macr"))
                fprintf(fptr, "%s", line);
            else {
                printf("Line must contain only a macro definition!\n");
                foundErr = EXIT_FAILURE;
                continue;
            }

        }

        else {
            nextToken(str, &ptr, ' ');
            if(*str || !(*name)) {
                printf("Line must contain only a macro definition!\n");
                foundErr = EXIT_FAILURE;
                continue;
            }

            if(isLegalMacrName(&tb, name)) {
                exit_code = save_macr(&tb, name, fp, fptr);
                if(exit_code) return exit_code;
            } else {
                printf("Invalid macro name!\n");
                foundErr = EXIT_FAILURE;
                continue;
            }
        }
    }

    freeMacrTable(&tb);
    fclose(fp);
    fclose(fptr);
    return foundErr;
}
