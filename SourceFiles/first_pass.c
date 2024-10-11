/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file first_pass.c
 * @brief Handles the first pass of the assembler process.
 *
 * This file contains the function `first_pass`, which processes an assembly
 * file, identifying labels, directives and opcodes, and performs
 * initial memory allocation and error handling.
 */

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

/**
 * @brief Performs the first pass of the assembler.
 *
 * This function reads through the assembly file line by line, processing
 * labels, directives, and opcodes. It handles memory allocation, error checking,
 * and builds the label table and instruction/data memory. The first pass is
 * crucial for identifying and preparing for the second pass.
 *
 * @param file_name The name of the file to be processed (without extension).
 * @param macr_tb A pointer to the macro table.
 * @return int Returns `EXIT_SUCCESS` if the first pass completes successfully,
 *         or `EXIT_FAILURE` if an error occurs.
 */
int first_pass(char *file_name, macr_table *macr_tb) {
    char line[MAX_LINE_SIZE + 1], str[MAX_LINE_SIZE + 1], *ptr;
    unsigned short instructions[MEMORY_SIZE] = {0}, data[MEMORY_SIZE] = {0};
    unsigned short *iptr = instructions, *dptr = data;
    int IC = 0, DC = 0, is_out_of_memory = 0, is_entry = 0, is_extern = 0;
    int foundErr = EXIT_SUCCESS, line_counter = 0, extra_words;
    label_table label_tb;
    label *lb = NULL;
    opcode op;
    FILE *fp;

    /* Initialize the label table */
    initLabelTable(&label_tb);

    printf(">>> Started working on the file %s.am\n", file_name);

    /* Open the preprocessed file with the ".am" suffix */
    fp = open_file_with_suffix(file_name, ".am", "r", NULL, macr_tb, NULL, NULL, NULL);

    /* Process each line of the file */
    while((ptr = fgets(line, MAX_LINE_SIZE + 1, fp))) {
        line_counter++;

        /* Skip comment lines */
        if(*ptr == ';') continue;

        /* Extract the first token from the line */
        nextToken(str, &ptr, ' ');
        if(!(*str)) continue;

        /* Label found: check if the token ends with a colon */
        if(str[strlen(str) - 1] == ':') {
            str[strlen(str) - 1] = '\0';  /* Remove colon */

            lb = find_label(&label_tb, str);  /* Find if the label already exists */
            if(lb && (lb->is_extern || lb->is_entry > 1)) {
                printError(line_counter, MULTIPLE_MACRO_DEFINITIONS);
                foundErr = EXIT_FAILURE;
                lb = NULL;
                continue;
            }

            /* Parse the label and check for errors */
            if(parseLabel(&label_tb, macr_tb, str, fp)) {
                printError(line_counter, INVALID_LABEL);
                foundErr = EXIT_FAILURE;
                continue;
            }
            lb = find_label(&label_tb, str);
            nextToken(str, &ptr, ' ');
        }

        /* Check for data directives (e.g., .data, .string) */
        if(!strcmp(str, ".data") || !strcmp(str, ".string")) {
            if(!strcmp(str, ".data"))
                extra_words = isLegalData(ptr, dptr, DC, line_counter);
            else
                extra_words = isLegalString(ptr, dptr, DC, line_counter);

            if(!extra_words) {
                foundErr = EXIT_FAILURE;
                continue;
            }

            /* Assign label to data section */
            if(lb) {
                lb->address = DC;
                lb->is_data = 1;
            }
            DC += extra_words, dptr += extra_words, lb = NULL;

            /* Check for opcode instructions */
        } else if((op = get_opcode(str)) != unknown_opcode) {
            extra_words = isLegalOpcode(op, ptr, iptr, IC, line_counter, &label_tb, macr_tb);
            if(!extra_words) {
                foundErr = EXIT_FAILURE;
                continue;
            }

            /* Assign label to instruction section */
            if(lb)
                lb->address = IC + 100;
            IC += extra_words, iptr += extra_words, lb = NULL;

            /* Handle .entry and .extern directives */
        } else if(!strcmp(str, ".entry") || !strcmp(str, ".extern")) {
            if(lb)
                delLabelFromTable(&label_tb, lb);

            if(!strcmp(str, ".entry"))
                is_entry = 1;
            else
                is_extern = 1;

            nextToken(str, &ptr, ' ');
            lb = find_label(&label_tb, str);
            if(lb && (lb->is_entry || lb->is_extern || is_extern)) {
                printError(line_counter, MULTIPLE_MACRO_DEFINITIONS);
                foundErr = EXIT_FAILURE;
                continue;
            }

            /* Parse the label for entry/extern */
            if(parseLabel(&label_tb, macr_tb, str, fp)) {
                printError(line_counter, INVALID_LABEL);
                foundErr = EXIT_FAILURE;
                continue;
            }
            lb = find_label(&label_tb, str);
            lb->is_entry = is_entry, lb->is_extern = is_extern;
            is_entry = 0, is_extern = 0, lb = NULL;

            /* Error for missing dot in directive */
        } else if(!strcmp(str, "entry") || !strcmp(str, "extern") ||
                  !strcmp(str, "data") || !strcmp(str, "string")) {
            printError(line_counter, MISSING_DOT_IN_DIRECTIVE);
            foundErr = EXIT_FAILURE;

            /* Unrecognized command or label */
        } else {
            if(lb)
                delLabelFromTable(&label_tb, lb), lb = NULL;
            printError(line_counter, UNRECOGNIZED_COMMAND);
            foundErr = EXIT_FAILURE;
        }

        /* Check for memory overflow */
        if(IC + DC >= MEMORY_SIZE && !is_out_of_memory) {
            printf("    %s\n", getError(MEMORY_OVERFLOW));
            is_out_of_memory = 1;
            foundErr = EXIT_FAILURE;
        }
    }

    /* Adjust the address of data labels based on the instruction counter */
    increaseDataLabelTableAddress(&label_tb, IC + 100);

    /* Free memory used by the macro table */
    freeMacrTable(macr_tb);
    fclose(fp);

    /* If an error was found, free label table and exit */
    if(foundErr) {
        printf(">>> Finished working on the file %s.am\n", file_name);
        freeLabelTable(&label_tb);
        return EXIT_FAILURE;
    }

    /* Proceed to the second pass */
    return second_pass(file_name, &label_tb, instructions, data, DC);
}
