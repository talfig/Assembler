#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "label.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "globals.h"
#include "errors_handling.h"
#include "first_pass.h"
#include "second_pass.h"
#include "file_utils.h"

int first_pass(char *file_name, macr_table *macr_tb) {
    char line[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 2], *ptr;
    unsigned short instructions[MEMORY_SIZE] = {0}, data[MEMORY_SIZE] = {0};
    unsigned short *iptr = instructions, *dptr = data;
    int IC = 0, DC = 0, is_out_of_memory = 0, is_entry = 0, is_extern = 0;
    int foundErr = EXIT_SUCCESS, line_counter = 0, extra_words;
    label_table label_tb;
    label *lb = NULL;
    opcode op;
    FILE *fp;
    emptyLabelTable(&label_tb);

    printf(">>> Started working on the file %s%s\n", file_name, ".am");
    fp = open_file_with_suffix(file_name, ".am", "r", NULL, macr_tb, NULL, NULL, NULL);

    while((ptr = fgets(line, MAX_LINE_SIZE + 1, fp))) {
        line_counter++;

        if(*ptr == ';') continue;

        nextToken(str, &ptr, ' ');
        if(!(*str)) continue;

        /* Label found */
        if(str[strlen(str) - 1] == ':') {
            str[strlen(str) - 1] = '\0';

            lb = find_label(&label_tb, str);
            if(lb && (lb->is_extern || lb->is_entry > 1)) {
                printError(line_counter, MULTIPLE_MACRO_DEFINITIONS);
                foundErr = EXIT_FAILURE;
                lb = NULL;
                continue;
            }
            if(parseLabel(&label_tb, macr_tb, str, fp)) {
                printError(line_counter, INVALID_LABEL);
                foundErr = EXIT_FAILURE;
                continue;
            }
            lb = find_label(&label_tb, str);
            nextToken(str, &ptr, ' ');
        }

        /* Check for data directives, opcodes, or labels */
        if(!strcmp(str, ".data") || !strcmp(str, ".string")) {
            if(!strcmp(str, ".data"))
                extra_words = isLegalData(ptr, dptr, DC, line_counter);
            else extra_words = isLegalString(ptr, dptr, DC, line_counter);

            if(!extra_words) {
                foundErr = EXIT_FAILURE;
                continue;
            }
            if(lb) {
                lb->address = DC;
                lb->is_data = 1;
            }
            DC += extra_words, dptr += extra_words, lb = NULL;
        } else if((op = get_opcode(str)) != unknown_opcode) {
            extra_words = isLegalOpcode(op, ptr, iptr, IC, line_counter, &label_tb, macr_tb);
            if(!extra_words) {
                foundErr = EXIT_FAILURE;
                continue;
            }
            if(lb) lb->address = IC + 100;
            IC += extra_words, iptr += extra_words, lb = NULL;
        } else if(!strcmp(str, ".entry") || !strcmp(str, ".extern")) {
            if(lb) delLabelFromTable(&label_tb, lb);

            if(!strcmp(str, ".entry")) is_entry = 1;
            else is_extern = 1;

            nextToken(str, &ptr, ' ');
            lb = find_label(&label_tb, str);
            if(lb && (lb->is_entry || lb->is_extern || is_extern)) {
                printError(line_counter, MULTIPLE_MACRO_DEFINITIONS);
                foundErr = EXIT_FAILURE;
                continue;
            }
            if(parseLabel(&label_tb, macr_tb, str, fp)) {
                printError(line_counter, INVALID_LABEL);
                foundErr = EXIT_FAILURE;
                continue;
            }
            lb = find_label(&label_tb, str);
            lb->is_entry = is_entry, lb->is_extern = is_extern;
            is_entry = 0, is_extern = 0, lb = NULL;
        } else if(!strcmp(str, "entry") || !strcmp(str, "extern") ||
                   !strcmp(str, "data") || !strcmp(str, "string")) {
            printError(line_counter, MISSING_DOT_IN_DIRECTIVE);
            foundErr = EXIT_FAILURE;
        } else {
            if(lb) delLabelFromTable(&label_tb, lb), lb = NULL;
            printError(line_counter, UNRECOGNIZED_COMMAND);
            foundErr = EXIT_FAILURE;
        }

        if(IC + DC >= MEMORY_SIZE && !is_out_of_memory) {
            printf("    %s\n", getError(MEMORY_OVERFLOW));
            is_out_of_memory = 1;
            foundErr = EXIT_FAILURE;
        }
    }

    increaseDataLabelTableAddress(&label_tb, IC + 100);
    freeMacrTable(macr_tb);
    fclose(fp);

    if(foundErr) {
        printf(">>> Finished working on the file %s%s\n", file_name, ".am");
        freeLabelTable(&label_tb);
        return EXIT_FAILURE;
    }

    return second_pass(file_name, &label_tb, instructions, data, DC);
}
