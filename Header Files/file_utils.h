/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file file_utils.h
 * @brief This header file declares the functions used for processing files, managing memory,
 * and handling errors during the assembly process.
 */

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include "label.h"

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
                    macr_table *macr_tb, FILE *fp1, FILE *fp2, FILE *fp3);

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
                            label_table *label_tb, macr_table *macr_tb, FILE *fp1, FILE *fp2, FILE *fp3);

/**
 * @brief Prints the instructions stored in memory to the specified file.
 *
 * @param ptr Pointer to the array of instructions.
 * @param IC The instruction count.
 * @param fp The file pointer where the instructions will be printed.
 */
void print_instructions(unsigned short *ptr, int IC, FILE *fp);

/**
 * @brief Prints the data section stored in memory to the specified file.
 *
 * @param ptr Pointer to the array of data.
 * @param IC The instruction count to offset the data indices.
 * @param DC The data count.
 * @param fp The file pointer where the data will be printed.
 */
void print_data(unsigned short *ptr, int IC, int DC, FILE *fp);

/**
 * @brief Creates an entry file listing all labels marked as entry.
 *
 * @param label_tb Pointer to the label table.
 * @param fp The file pointer where the entry labels will be printed.
 */
void create_entry_file(label_table *label_tb, FILE *fp);

/**
 * @brief Closes multiple files safely.
 *
 * @param fp1 Pointer to the first file.
 * @param fp2 Pointer to the second file.
 * @param fp3 Pointer to the third file.
 * @param fp4 Pointer to the fourth file.
 */
void close_multiple_files(FILE *fp1, FILE *fp2, FILE *fp3, FILE *fp4);

/**
 * @brief Removes a file from the file system.
 *
 * @param file_name The name of the file to be removed.
 */
void remove_file(const char *file_name);

/**
 * @brief Processes a file by appending a suffix and removing the resulting file.
 *
 * @param file_name The original file name.
 * @param suffix The suffix to append.
 * @param label_tb Pointer to the label table (used if necessary).
 */
void process_file(const char *file_name, const char *suffix, void *label_tb);

/**
 * @brief The main assembler function.
 *
 * This function processes command-line arguments and runs the preprocessor on each input file.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return int Returns 1 if errors were found, otherwise returns 0.
 */
int assembler(int argc, char *argv[]);

#endif /* FILE_UTILS_H */
