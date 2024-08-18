/**
 * @file preprocessor.c
 * @brief Handles the preprocessing of assembly files, specifically macro expansion.
 *
 * This file contains the implementation of the preprocessor function, which processes
 * an assembly source file (.as), expands macros, and writes the result to an output file (.am).
 * The function also performs error checking during macro expansion and reports any issues.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "errors_handling.h"
#include "first_pass.h"
#include "file_utils.h"

/**
 * @brief Preprocesses an assembly source file, expanding macros and writing the result to an output file.
 *
 * This function reads the input file line by line, expands any macros encountered, and writes
 * the processed lines to an output file. It also performs error checking and reports any issues
 * encountered during preprocessing.
 *
 * @param file_name The name of the source file (without extension) to be preprocessed.
 * @return int Returns EXIT_SUCCESS if preprocessing is successful, or EXIT_FAILURE if an error occurs.
 */
int preprocessor(char *file_name) {
    /* Buffer to hold a line read from the file */
    char line[MAX_LINE_SIZE + 2], str[MAX_LINE_SIZE + 1], name[MAX_LINE_SIZE + 1], *file_name_am, *ptr;
    int foundErr = EXIT_SUCCESS, line_counter = 0, exit_code;
    FILE *fp_in, *fp_out;
    macr *mcr;
    macr_table macr_tb;

    /* Initialize the macro table */
    initMacrTable(&macr_tb);

    /* Notify that preprocessing has started */
    printf(">>> Started working on the file %s.as\n", file_name);

    /* Open the input (.as) and output (.am) files */
    fp_in = open_file_with_suffix(file_name, ".as", "r", NULL, NULL, NULL, NULL, NULL);
    fp_out = open_file_with_suffix(file_name, ".am", "w", NULL, NULL, fp_in, NULL, NULL);

    /* Process each line of the input file */
    while((ptr = fgets(line, MAX_LINE_SIZE + 2, fp_in))) {
        line_counter++;

        /* Check for errors in the current line */
        if(checkLine(fp_in, line, line_counter)) {
            foundErr = EXIT_FAILURE;
            continue;
        }

        nextToken(str, &ptr, ' ');
        nextToken(name, &ptr, ' ');

        /* Check if the first token is a macro name */
        mcr = find_macr(&macr_tb, str);

        if(mcr) {
            /* If there is extraneous text after the macro, report an error */
            if(*name) {
                printError(line_counter, EXTRANEOUS_TEXT_AFTER_MACRO);
                foundErr = EXIT_FAILURE;
            }
            /* Write the macro's content to the output file */
            else fprintf(fp_out, "%s", mcr->info);
        }
        /* If the line is not a macro definition, write it to the output file */
        else if(strcmp(str, "macr") != 0) fprintf(fp_out, "%s", line);
        else {
            /* Handle macro definition */
            nextToken(str, &ptr, ' ');

            /* Check for errors in macro definition syntax */
            if(*str || !(*name)) {
                if(*str)
                    printError(line_counter, EXTRANEOUS_TEXT_AFTER_MACRO);
                else
                    printError(line_counter, MISSING_NAME_IN_MACRO);
                foundErr = EXIT_FAILURE;
                continue;
            }

            /* Check if the macro name is legal and save it */
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

    /* Handle errors found during preprocessing */
    if(foundErr) {
        file_name_am = append_suffix(file_name, ".am", NULL, &macr_tb, NULL, NULL, NULL);
        remove_file(file_name_am);
        printf(">>> Finished working on the file %s.as\n", file_name);
        free(file_name_am);
        freeMacrTable(&macr_tb);
        return EXIT_FAILURE;
    }

    /* Notify that preprocessing finished without errors */
    printf("    No errors were found in the file %s.as during macro expansion\n", file_name);
    printf(">>> Finished working on the file %s.as\n", file_name);

    /* Proceed with the first pass after preprocessing */
    return first_pass(file_name, &macr_tb);
}
