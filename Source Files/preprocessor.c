#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "errors_handling.h"
#include "first_pass.h"
#include "file_utils.h"

int preprocessor(char *file_name) {
    char line[MAX_LINE_SIZE + 2], str[MAX_LINE_SIZE + 1], name[MAX_LINE_SIZE + 1], *file_name_am, *ptr;
    int foundErr = EXIT_SUCCESS, line_counter = 0, exit_code;
    FILE *fp_in, *fp_out;
    macr *mcr;
    macr_table macr_tb;
    emptyMacrTable(&macr_tb);

    printf(">>> Started working on the file %s%s\n", file_name, ".as");
    fp_in = open_file_with_suffix(file_name, ".as", "r", NULL, NULL, NULL, NULL, NULL);
    fp_out = open_file_with_suffix(file_name, ".am", "w", NULL, NULL, fp_in, NULL, NULL);

    while((ptr = fgets(line, MAX_LINE_SIZE + 2, fp_in))) {
        line_counter++;
        if(checkLine(fp_in, line, line_counter)) foundErr = EXIT_FAILURE;

        nextToken(str, &ptr, ' ');
        nextToken(name, &ptr, ' ');
        mcr = find_macr(&macr_tb, str);

        if(mcr) {
            if(*name) {
                printError(line_counter, EXTRANEOUS_TEXT_AFTER_MACRO);
                foundErr = EXIT_FAILURE;
            }
            else fprintf(fp_out, "%s", mcr->info);
        }

        else if(strcmp(str, "macr") != 0) fprintf(fp_out, "%s", line);

        else {
            nextToken(str, &ptr, ' ');
            if(*str || !(*name)) {
                if(*str)
                    printError(line_counter, EXTRANEOUS_TEXT_AFTER_MACRO);
                else printError(line_counter, MISSING_NAME_IN_MACRO);
                foundErr = EXIT_FAILURE;
                continue;
            }

            if(isLegalMacrName(&macr_tb, name)) {
                exit_code = save_macr(&macr_tb, name, line_counter, fp_in, fp_out);
                if(exit_code == EXIT_FAILURE) foundErr = EXIT_FAILURE;
                line_counter = exit_code;
            } else {
                printError(line_counter, INVALID_MACRO_NAME);
                foundErr = EXIT_FAILURE;
            }
        }
    }

    fclose(fp_in);
    fclose(fp_out);
    if(foundErr) {
        file_name_am = append_suffix(file_name, ".am", NULL, &macr_tb, NULL, NULL, NULL);
        remove_file(file_name_am);
        printf(">>> Finished working on the file %s%s\n", file_name, ".as");
        free(file_name_am);
        freeMacrTable(&macr_tb);
        return EXIT_FAILURE;
    }

    printf(">>> Finished working on the file %s%s\n", file_name, ".as");
    return first_pass(file_name, &macr_tb);
}
