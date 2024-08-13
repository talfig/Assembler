#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "label.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "globals.h"
#include "errors.h"
#include "first_pass.h"
#include "second_pass.h"

int first_pass(char *file_name, macr_table *macr_tb) {
    char line[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 2], *ptr;
    unsigned short instructions[MEMORY_SIZE] = {0}, data[MEMORY_SIZE] = {0};
    unsigned short *iptr = instructions, *dptr = data;
    int IC = 0, DC = 0, is_out_of_memory = 0, is_entry = 0;
    int foundErr = EXIT_SUCCESS, line_counter = 0, extra_words;
    label_table label_tb;
    label *lb = NULL;
    opcode op;
    FILE *fp;
    emptyLabelTable(&label_tb);

    fp = fopen(file_name, "r");
    openFail(fp);

    while((ptr = fgets(line, MAX_LINE_SIZE + 1, fp))) {
        line_counter++;

        if(*ptr == ';') continue;

        nextToken(str, &ptr, ' ');
        if(!(*str)) continue;

        /* Label found */
        if(str[strlen(str) - 1] == ':') {
            str[strlen(str) - 1] = '\0';

            if(parseLabel(&label_tb, macr_tb, str, fp)) {
                printf("Error: Invalid label at line %d.\n", line_counter);
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
            DC += extra_words, dptr += extra_words;
            if(!strcmp(str, ".string")) DC++, dptr++;
            lb = NULL;
        } else if((op = get_opcode(str)) != opcode_none) {
            extra_words = isLegalOpcode(op, ptr, iptr, IC, line_counter, &label_tb, macr_tb);
            if(!extra_words) {
                foundErr = EXIT_FAILURE;
                continue;
            }
            if(lb) lb->address = IC + 100;
            IC += extra_words, iptr += extra_words, lb = NULL;
        } else if(!strcmp(str, ".entry") || !strcmp(str, ".extern")) {
            if(!strcmp(str, ".entry")) is_entry = 1;

            nextToken(str, &ptr, ' ');
            lb = find_label(&label_tb, str);
            if(!(lb && !lb->is_entry && !lb->is_extern && is_entry)) {
                if((lb && lb->is_entry) || parseLabel(&label_tb, macr_tb, str, fp)) {
                    printf("Error: Invalid label in at line %d.\n", line_counter);
                    foundErr = EXIT_FAILURE;
                    continue;
                }
            }
            lb = find_label(&label_tb, str);
            if(is_entry) lb->is_entry = 1;
            else lb->is_extern = 1;
            is_entry = 0, lb = NULL;
        } else if(!strcmp(str, "entry") || !strcmp(str, "extern") ||
                   !strcmp(str, "data") || !strcmp(str, "string")) {
            printf("Error: Missing '.' in directive at line %d.\n", line_counter);
            foundErr = EXIT_FAILURE;
        } else {
            printf("Error: Unrecognized command or label at line %d.\n", line_counter);
            foundErr = EXIT_FAILURE;
        }

        if(IC + DC >= MEMORY_SIZE && !is_out_of_memory) {
            printf("Error: Out of memory.\n");
            is_out_of_memory = 1;
            foundErr = EXIT_FAILURE;
        }
    }

    increaseDataLabelTableAddress(&label_tb, IC + 100);
    freeMacrTable(macr_tb);
    fclose(fp);

    if(foundErr) {
        freeLabelTable(&label_tb);
        return EXIT_FAILURE;
    }

    return second_pass("out.txt", &label_tb, instructions, data, DC);
}
