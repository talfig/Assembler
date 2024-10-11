/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file opcode_utils.h
 * @brief Header file for utility functions related to opcode encoding and parsing.
 *
 * This header file declares functions used for encoding opcodes, determining
 * addressing methods, and parsing assembly instructions.
 */

#ifndef OPCODE_UTILS_H
#define OPCODE_UTILS_H

#include "label.h"
#include "macr.h"

/**
 * @def CLEAR_MSB
 * @brief Mask to clear the most significant bit of a 16-bit word.
 */
#define CLEAR_MSB 0x7FFF

/**
 * @brief Determines the addressing method based on the given string.
 *
 * This function checks the provided string against various addressing methods
 * and returns the corresponding method type.
 *
 * @param label_tb Pointer to the label table.
 * @param macr_tb Pointer to the macro table.
 * @param str The string representing the address.
 * @param line_counter The line number of the instruction.
 * @return Addressing method type (0-3) or -1 if not recognized.
 */
int which_address_method(label_table *label_tb, macr_table *macr_tb, char *str, int line_counter);

/**
 * @brief Encodes the first word of an instruction with the given opcode and operands.
 *
 * This function sets the opcode, addressing methods, and other bits in the
 * first word of an instruction, preparing it for storage or further processing.
 *
 * @param ptr Pointer to the word to encode.
 * @param op The opcode to encode.
 * @param opr1 The first operand's addressing method.
 * @param opr2 The second operand's addressing method.
 */
void encode_first_word(unsigned short *ptr, opcode op, int opr1, int opr2);

/**
 * @brief Parses an opcode instruction and encodes the corresponding words.
 *
 * This function parses the given opcode string and its operands, determining
 * the addressing methods and encoding the instruction accordingly.
 *
 * @param ptr Pointer to the string containing the opcode.
 * @param iptr Pointer to the pointer to the instruction word.
 * @param idx The index to use for encoding.
 * @param line_counter The line number of the instruction.
 * @param label_tb Pointer to the label table.
 * @param fp Pointer to the output file for external label information.
 * @return EXIT_SUCCESS on successful parsing, EXIT_FAILURE on error.
 */
int parseOpcode(char *ptr, unsigned short **iptr, int idx, int line_counter, label_table *label_tb, FILE *fp);

#endif /* OPCODE_UTILS_H */
