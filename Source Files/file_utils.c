/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file file_utils.c
 * @brief This file contains the implementation of the assembler functions for processing files, managing memory,
 * and handling errors during the assembly process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"
#include "label.h"
#include "macr.h"
#include "errors_handling.h"
#include "file_utils.h"

/**
 * @brief Appends a suffix to a given string and returns the new string.
 *
 * @param str The original string.
 * @param suffix The suffix to append.
 * @param label_tb Pointer to the label table for memory cleanup in case of failure.
 * @param macr_tb Pointer to the macro table for memory cleanup in case of failure.
 * @param fp1 Pointer to the first file for cleanup in case of failure.
 * @param fp2 Pointer to the second file for cleanup in case of failure.
 * @param fp3 Pointer to the third file for cleanup in case of failure.
 * @return char* The newly created string with the suffix appended.
 */
char *append_suffix(const char *str, const char *suffix, label_table *label_tb,
                    macr_table *macr_tb, FILE *fp1, FILE *fp2, FILE *fp3) {
    size_t len1 = strlen(str);
    size_t len2 = strlen(suffix);
    char *result = (char *)malloc(len1 + len2 + 1);

    /* Check if memory allocation failed */
    if(!result) {
        fprintf(stderr, "    %s\n", getError(ALLOC_FAILED));
        if(label_tb) freeLabelTable(label_tb);
        if(macr_tb) freeMacrTable(macr_tb);
        close_multiple_files(fp1, fp2, fp3, NULL);
        exit(EXIT_FAILURE);
    }

    sprintf(result, "%s%s", str, suffix);
    return result;
}

/**
 * @brief Opens a file with a specified suffix and mode.
 *
 * @param file_name The name of the file to open.
 * @param suffix The suffix to append to the file name.
 * @param mode The mode in which to open the file (e.g., "r", "w").
 * @param label_tb Pointer to the label table for memory cleanup in case of failure.
 * @param macr_tb Pointer to the macro table for memory cleanup in case of failure.
 * @param fp1 Pointer to the first file for cleanup in case of failure.
 * @param fp2 Pointer to the second file for cleanup in case of failure.
 * @param fp3 Pointer to the third file for cleanup in case of failure.
 * @return FILE* The file pointer of the opened file.
 */
FILE *open_file_with_suffix(const char *file_name, const char *suffix, const char *mode,
                            label_table *label_tb, macr_table *macr_tb, FILE *fp1, FILE *fp2, FILE *fp3) {
    char *file_name_with_suffix = append_suffix(file_name, suffix, label_tb, macr_tb, fp1, fp2, fp3);
    FILE *fp = fopen(file_name_with_suffix, mode);

    /* Check if the file opening failed */
    if(!fp) {
        fprintf(stderr, "    %s %s\n", getError(FILE_OPEN_FAILED), file_name_with_suffix);
        if(label_tb) freeLabelTable(label_tb);
        if(macr_tb) freeMacrTable(macr_tb);
        free(file_name_with_suffix);
        close_multiple_files(fp1, fp2, fp3, NULL);
        exit(EXIT_FAILURE);
    }

    free(file_name_with_suffix);
    return fp;
}

/**
 * @brief Prints the instructions stored in memory to the specified file.
 *
 * @param ptr Pointer to the array of instructions.
 * @param IC The instruction count.
 * @param fp The file pointer where the instructions will be printed.
 */
void print_instructions(unsigned short *ptr, int IC, FILE *fp) {
    int i;

    for(i = 0; i < IC; i++) {
        if(i < 1000)  fprintf(fp, "0"); /* Ensure consistent formatting for indices below 1000 */
        fprintf(fp, "%d ", 100 + i);
        fprintf(fp, "%05o\n", ptr[i]);
    }
}

/**
 * @brief Prints the data section stored in memory to the specified file.
 *
 * @param ptr Pointer to the array of data.
 * @param IC The instruction count to offset the data indices.
 * @param DC The data count.
 * @param fp The file pointer where the data will be printed.
 */
void print_data(unsigned short *ptr, int IC, int DC, FILE *fp) {
    int i;

    for(i = 0; i < DC; i++) {
        if(i < 1000)  fprintf(fp, "0"); /* Ensure consistent formatting for indices below 1000 */
        fprintf(fp, "%d ", 100 + IC + i);
        fprintf(fp, "%05o\n", ptr[i]);
    }
}

/**
 * @brief Creates an entry file listing all labels marked as entry.
 *
 * @param label_tb Pointer to the label table.
 * @param fp The file pointer where the entry labels will be printed.
 */
void create_entry_file(label_table *label_tb, FILE *fp) {
    label *ptr = label_tb->head;

    while(ptr) {
        if(ptr->is_entry) {
            fprintf(fp, "%s ", ptr->name);
            if(ptr->address < 1000)  fprintf(fp, "0"); /* Ensure consistent formatting for addresses below 1000 */
            fprintf(fp, "%d\n", ptr->address);
        }
        ptr = ptr->next;
    }
}

/**
 * @brief Closes multiple files safely.
 *
 * @param fp1 Pointer to the first file.
 * @param fp2 Pointer to the second file.
 * @param fp3 Pointer to the third file.
 * @param fp4 Pointer to the fourth file.
 */
void close_multiple_files(FILE *fp1, FILE *fp2, FILE *fp3, FILE *fp4) {
    if(fp1) fclose(fp1);
    if(fp2) fclose(fp2);
    if(fp3) fclose(fp3);
    if(fp4) fclose(fp4);
}

/**
 * @brief Removes a file from the file system.
 *
 * @param file_name The name of the file to be removed.
 */
void remove_file(const char *file_name) {
    if(remove(file_name))
        fprintf(stderr, "    %s %s\n", getError(FILE_DELETION_FAILED), file_name);
}

/**
 * @brief Processes a file by appending a suffix and removing the resulting file.
 *
 * @param file_name The original file name.
 * @param suffix The suffix to append.
 * @param label_tb Pointer to the label table (used if necessary).
 */
void process_file(const char *file_name, const char *suffix, void *label_tb) {
    char *file_name_with_suffix = append_suffix(file_name, suffix, label_tb, NULL, NULL, NULL, NULL);
    remove_file(file_name_with_suffix);
    free(file_name_with_suffix);
}

/**
 * @brief The main assembler function.
 *
 * This function processes command-line arguments and runs the preprocessor on each input file.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return int Returns 1 if errors were found, otherwise returns 0.
 */
int assembler(int argc, char *argv[]) {
    int i, foundErr = 0;

    /* Check if at least one input file was provided */
    if(argc < 2) {
        fprintf(stderr, "%s\n", getError(MISSING_ARGUMENT));
        exit(EXIT_FAILURE);
    }

    /* Process each input file */
    for(i = 1; i < argc; i++) {
        if(preprocessor(argv[i]))
            foundErr = 1;
    }

    return foundErr;
}
