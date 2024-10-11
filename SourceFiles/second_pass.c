/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file second_pass.c
 * @brief Handles the second pass of the assembler process.
 *
 * This file contains the implementation of the second pass function, which processes
 * an assembly file that has been preprocessed to expand macros. It resolves labels,
 * encodes instructions and data, and generates the final output files (.ob, .ent, .ext).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "globals.h"
#include "opcode_utils.h"
#include "file_utils.h"
#include "errors_handling.h"

/**
 * @brief Performs the second pass on an assembly source file.
 *
 * This function processes an assembly file that has been preprocessed to expand macros.
 * During the second pass, it resolves labels, encodes instructions and data, and generates
 * the final output files (.ob for object code, .ent for entry points, and .ext for external references).
 *
 * @param file_name The name of the source file (without extension) to be processed.
 * @param label_tb A pointer to the label table used for label resolution.
 * @param instructions An array of unsigned short where the instructions will be stored.
 * @param data An array of unsigned short where the data will be stored.
 * @param DC The data counter, indicating the amount of data in the file.
 * @return int Returns EXIT_SUCCESS if the second pass is successful, or EXIT_FAILURE if an error occurs.
 */
int second_pass(char *file_name, label_table *label_tb, unsigned short *instructions, unsigned short *data, int DC) {
    /* Buffer to hold a line read from the file */
    char line[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 1], *ptr;
    unsigned short foundErr = EXIT_SUCCESS, line_counter = 0, IC = 0;
    unsigned short *iptr = instructions;
    label *lb = NULL;
    FILE *fp_in, *fp_out, *fp_ent, *fp_ext;

    /* Open the necessary files for the second pass */
    fp_in = open_file_with_suffix(file_name, ".am", "r", label_tb, NULL, NULL, NULL, NULL);
    fp_out = open_file_with_suffix(file_name, ".ob", "w", label_tb, NULL, fp_in, NULL, NULL);
    fp_ent = open_file_with_suffix(file_name, ".ent", "w", label_tb, NULL, fp_in, fp_out, NULL);
    fp_ext = open_file_with_suffix(file_name, ".ext", "w", label_tb, NULL, fp_in, fp_out, fp_ent);

    /* Process each line of the input file */
    while((ptr = fgets(line, MAX_LINE_SIZE + 1, fp_in))) {
        line_counter++;

        /* Skip comment lines */
        if(*ptr == ';') continue;

        nextToken(str, &ptr, ' ');
        if(!(*str)) continue;

        /* If a label is found, move to the next token */
        if(str[strlen(str) - 1] == ':') nextToken(str, &ptr, ' ');

        /* Check for data directives, opcodes, or labels */
        if(!strcmp(str, ".data") || !strcmp(str, ".string") || !strcmp(str, ".extern")) continue;
        else if(!strcmp(str, ".entry")) {
            nextToken(str, &ptr, ' ');
            lb = find_label(label_tb, str);
            if(lb && !lb->address) {
                printError(line_counter, ENTRY_LABEL_UNDEFINED);
                foundErr = EXIT_FAILURE;
            }
        } else if(get_opcode(str) != unknown_opcode) {
            iptr++, IC++;
            if(parseOpcode(ptr, &iptr, IC, line_counter, label_tb, fp_ext)) {
                foundErr = EXIT_FAILURE;
                continue;
            }
            IC = iptr - instructions;
        }
    }

    /* Write the instruction and data counts to the output file */
    fprintf(fp_out, "  %d %d\n", IC, DC);
    print_instructions(instructions, IC, fp_out);
    print_data(data, IC, DC, fp_out);
    create_entry_file(label_tb, fp_ent);

    /* Close all the opened files */
    close_multiple_files(fp_in, fp_out, fp_ent, fp_ext);

    /* Handle errors and file processing based on labels */
    if(foundErr) process_file(file_name, ".ob", label_tb);
    if(foundErr || !has_entry_label(label_tb)) process_file(file_name, ".ent", label_tb);
    if(foundErr || !has_extern_label(label_tb)) process_file(file_name, ".ext", label_tb);

    /* Notify if no errors were found */
    if(!foundErr) printf("    No errors were found in the file %s.am\n", file_name);
    printf(">>> Finished working on the file %s.am\n", file_name);
    freeLabelTable(label_tb);

    return foundErr;
}
