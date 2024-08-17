/**
 * @file assembler.c
 * @brief Entry point for the assembler program.
 *
 * This file contains the main function which serves as the entry point for the
 * assembler program. The main function simply passes command-line arguments to
 * the assembler function defined in `file_utils.h`.
 */

#include "file_utils.h"

/**
 * @brief Main function of the assembler program.
 *
 * This function acts as the entry point for the assembler program. It takes
 * command-line arguments and passes them to the assembler function.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of pointers to the command-line arguments.
 * @return Returns the exit status of the assembler function.
 */
int main(int argc, char *argv[]) {
    return assembler(argc, argv);
}
