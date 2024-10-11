/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file first_pass.h
 * @brief This header file declares the functions and macros used in the first pass of the assembler,
 * which processes assembly source code and generates intermediate code.
 */

#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include "macr.h"

/**
 * @def MEMORY_SIZE
 * @brief Size of the memory in the assembler, measured in words.
 */
#define MEMORY_SIZE 4096

/**
 * @brief Performs the first pass of the assembler.
 *
 * This function processes the input assembly file, expands macros, and stores the intermediate code
 * in memory. It also handles label definitions and macro expansions.
 *
 * @param file_nam The name of the input file to be processed.
 * @param macr_tb Pointer to the macro table used for storing and expanding macros.
 * @return int Returns 0 on success, or a non-zero error code if an error occurs.
 */
int first_pass(char *file_nam, macr_table *macr_tb);

#endif /* FIRST_PASS_H */
