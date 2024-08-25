/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file preprocessor.h
 * @brief Header file for the preprocessor module.
 *
 * This header file contains the declaration of the preprocessor function and
 * relevant constants used for processing assembly source files. The preprocessor
 * function is responsible for macro expansion in assembly files.
 */

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdio.h>

/**
 * @def MAX_LINE_SIZE
 * @brief Maximum allowed size for a line in the assembly source file.
 */
#define MAX_LINE_SIZE 81

/**
 * @def MAX_LABEL_SIZE
 * @brief Maximum allowed size for a label in the assembly source file.
 */
#define MAX_LABEL_SIZE 31

/**
 * @brief Preprocesses an assembly source file, expanding macros.
 *
 * This function reads an assembly file, expands macros, and writes the
 * result to an output file. It also performs error checking and reports
 * any issues found during preprocessing.
 *
 * @param file_name The name of the source file (without extension) to be preprocessed.
 * @return int Returns EXIT_SUCCESS if preprocessing is successful, or EXIT_FAILURE if an error occurs.
 */
int preprocessor(char *file_name);

#endif /* PREPROCESSOR_H */
