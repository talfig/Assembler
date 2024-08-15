#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "errors.h"
#include "first_pass.h"
#include "file_utils.h"

int preprocessor(char *file_name) {
    char line[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 2], name[MAX_LABEL_SIZE + 2], *file_name_am, *ptr;
    int foundErr = EXIT_SUCCESS, line_counter = 0, exit_code;
    FILE *fp_in, *fp_out;
    macr *mcr;
    macr_table macr_tb;
    emptyMacrTable(&macr_tb);

    if(checkLines(file_name))
        foundErr = EXIT_FAILURE;

    fp_in = open_file_with_suffix(file_name, ".as", "r", NULL, NULL);
    file_name_am = append_suffix(file_name, ".am", NULL, NULL);
    fp_out = fopen(file_name_am, "w");
    free(file_name_am);
    if(!fp_out) {
        fprintf(stderr, "%s\n", getError(6));
        fclose(fp_in);
        exit(EXIT_FAILURE);
    }

    while((ptr = fgets(line, MAX_LINE_SIZE + 1, fp_in))) {
        line_counter++;
        nextToken(str, &ptr, ' ');
        nextToken(name, &ptr, ' ');
        mcr = find_macr(&macr_tb, str);

        if(mcr) {
            if(*name) {
                printf("Error found in line %d: %s\n", line_counter, getError(6));
                foundErr = EXIT_FAILURE;
                continue;
            }
            fprintf(fp_out, "%s", mcr->info);
        }

        else if(strcmp(str, "macr") != 0) {
            if(!strstr(ptr, "macr"))
                fprintf(fp_out, "%s", line);
            else {
                printf("Error found in line %d: %s\n", line_counter, getError(4));
                foundErr = EXIT_FAILURE;
                continue;
            }

        }

        else {
            nextToken(str, &ptr, ' ');
            if(*str || !(*name)) {
                if(!(*name))
                    printf("Error found in line %d: %s\n", line_counter, getError(10));
                else printf("Error found in line %d: %s\n", line_counter, getError(7));
                foundErr = EXIT_FAILURE;
                continue;
            }

            if(isLegalMacrName(&macr_tb, name)) {
                exit_code = save_macr(&macr_tb, name, line_counter, fp_in, fp_out);
                if(exit_code) return exit_code;
            } else {
                printf("Error found in line %d: %s\n", line_counter, getError(13));
                foundErr = EXIT_FAILURE;
                continue;
            }
        }
    }

    fclose(fp_in);
    fclose(fp_out);
    if(foundErr) {
        file_name_am = append_suffix(file_name, ".am", NULL, &macr_tb);
        remove_file(file_name_am, NULL, &macr_tb);
        free(file_name_am);
        freeMacrTable(&macr_tb);
        return EXIT_FAILURE;
    }

    return first_pass(file_name, &macr_tb);
}
