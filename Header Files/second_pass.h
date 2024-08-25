/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file second_pass.h
 * @brief Header file for the second pass of the assembler process.
 *
 * This header file contains the declaration of the second_pass function, which is
 * responsible for processing an assembly file after macro expansion. It resolves labels,
 * encodes instructions and data, and generates the final output files.
 */

#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "label.h"

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
int second_pass(char *file_name, label_table *label_tb, unsigned short *instructions, unsigned short *data, int DC);

#endif /* SECOND_PASS_H */
