/**
 * @file opcode_utils.c
 * @brief Utility functions for encoding and parsing opcodes in the assembler.
 *
 * This file contains functions to encode opcodes, parse addressing methods,
 * and handle labels in the assembler. Functions include checking address methods,
 * encoding words, and parsing opcode instructions.
 */

#include <stdlib.h>
#include "label.h"
#include "macr.h"
#include "integer_utils.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "opcode_utils.h"
#include "errors_handling.h"

/**
 * @brief Checks if a given string represents an instruction with value 0.
 *
 * @param str The string to check.
 * @param line_counter The line number of the instruction.
 * @return 1 if the string represents an instruction with value 0, 0 otherwise.
 *
 * This function checks if the string corresponds to an immediate addressing
 * method (method 0).
 */
int is0(char *str, int line_counter) {
    if(parseInstructionInt(str, line_counter) != INSTRUCTION_MAX_VALUE + 1)
        return 1;
    return 0;
}

/**
 * @brief Checks if a given string represents a label or legal label name.
 *
 * @param label_tb Pointer to the label table.
 * @param macr_tb Pointer to the macro table.
 * @param str The string to check.
 * @return 1 if the string represents a label or legal label name, 0 otherwise.
 *
 * This function checks if the string corresponds to a direct addressing method
 * (method 1).
 */
int is1(label_table *label_tb, macr_table *macr_tb, char *str) {
    if(find_label(label_tb, str) || isLegalLabelName(label_tb, macr_tb, str))
        return 1;
    return 0;
}

/**
 * @brief Checks if a given string represents a register with '*' prefix.
 *
 * @param str The string to check.
 * @return 1 if the string represents a register with '*' prefix, 0 otherwise.
 *
 * This function checks if the string corresponds to an indirect register
 * addressing method (method 2).
 */
int is2(char *str) {
    char *ptr = str;

    if(*ptr == '*' && get_register(ptr + 1) != unknown_register)
        return 1;
    return 0;
}

/**
 * @brief Checks if a given string represents a valid register.
 *
 * @param str The string to check.
 * @return 1 if the string represents a valid register, 0 otherwise.
 *
 * This function checks if the string corresponds to a direct register
 * addressing method (method 3).
 */
int is3(char *str) {
    if(get_register(str) != unknown_register)
        return 1;
    return 0;
}

/**
 * @brief Determines the addressing method based on the given string.
 *
 * @param label_tb Pointer to the label table.
 * @param macr_tb Pointer to the macro table.
 * @param str The string representing the address.
 * @param line_counter The line number of the instruction.
 * @return Addressing method type (0-3) or -1 if not recognized.
 *
 * This function identifies the addressing method by checking the string
 * against the known methods (0-3) and returns the corresponding method.
 */
int which_address_method(label_table *label_tb, macr_table *macr_tb, char *str, int line_counter) {
    if(is0(str, line_counter)) return 0;
    if(is1(label_tb, macr_tb, str)) return 1;
    if(is2(str)) return 2;
    if(is3(str)) return 3;
    return -1;
}

/**
 * @brief Encodes the first word of an instruction with the given opcode and operands.
 *
 * @param ptr Pointer to the word to encode.
 * @param op The opcode to encode.
 * @param opr1 The first operand.
 * @param opr2 The second operand.
 *
 * This function sets the opcode in the first word of the instruction and also
 * encodes the addressing methods for the operands in bits 3-6 and 7-10, respectively.
 * The structure and positioning of bits follow the table provided.
 */
void encode_first_word(unsigned short *ptr, opcode op, int opr1, int opr2) {
    *ptr |= op << 11;
    if(opr1 >= 0) *ptr |= 1 << (7 + opr1);
    if(opr2 >= 0) *ptr |= 1 << (3 + opr2);
    *ptr |= 1 << 2;
}

/**
 * @brief Checks if a label is legal, printing an error if not.
 *
 * @param str The label string to check.
 * @param line_counter The line number of the instruction.
 * @param label_tb Pointer to the label table.
 * @return 1 if the label is legal, 0 otherwise.
 */
int checkLabel(char *str, int line_counter, label_table *label_tb) {
    if(isLegalLabelName(label_tb, NULL, str)) {
        printError(line_counter, UNDEFINED_LABEL);
        return 0;
    }
    return 1;
}

/**
 * @brief Encodes an extra word based on the operand and label information.
 *
 * @param ptr Pointer to the word to encode.
 * @param idx The index to use for encoding.
 * @param opr1 The first operand.
 * @param opr2 The second operand.
 * @param str1 The string representation of the first operand.
 * @param label_tb Pointer to the label table.
 * @param fp Pointer to the output file.
 *
 * This function encodes the operand information into the extra word of the instruction.
 * It handles immediate values, direct addressing with labels, and register-based addressing.
 * The encoding respects the bit assignments as per the table provided.
 */
void encode_extra_word(unsigned short *ptr, int idx, int opr1, int opr2, char *str1, label_table *label_tb, FILE *fp) {
    int num;
    label *lb;
    regis rg;

    switch(opr1) {
        case 0:
            /* Immediate addressing: Encode the number directly into the instruction word */
            num = parseInstructionInt(str1, 0); /* 0 has no meaning */
            *ptr |= num << 3; /* Shift the immediate value to the correct bit position */
            *ptr |= 1 << 2; /* Set the relevant bit indicating immediate addressing */
            break;
        case 1:
            /* Direct addressing: Encode the label's address */
            lb = find_label(label_tb, str1);
            *ptr |= lb->address << 3; /* Shift the label address to the correct bit position */
            if(lb->is_extern) {
                fprintf(fp, "%s ", lb->name);
                if(100 + idx < 1000) fprintf(fp, "0");
                fprintf(fp, "%d\n", 100 + idx);
                lb->is_extern++;
                *ptr |= 1; /* Set the extern bit */
            }
            else *ptr |= 1 << 1;
            break;
        case 2:
            /* Internal label: Set the bit indicating internal addressing */
            str1++; /* Skip the '*' prefix */
            rg = get_register(str1);

            *ptr |= 1 << 2; /* Set the relevant bit indicating register addressing */
            if(opr2 == -1) *ptr |= rg << 3;  /* If only one operand, shift to the correct bit position */
            else *ptr |= rg << 6;            /* If two operands, shift accordingly */
            break;
        case 3:
            /* Direct register addressing: Similar to case 2 but without skipping the prefix */
            rg = get_register(str1);

            *ptr |= 1 << 2;  /* Set the relevant bit indicating register addressing */
            if(opr2 == -1) *ptr |= rg << 3;  /* If only one operand, shift to the correct bit position */
            else *ptr |= rg << 6;            /* If two operands, shift accordingly */
            break;
        default:
            /* No encoding needed for unsupported operand types */
            break;
    }
    *ptr &= CLEAR_MSB; /* Clear the most significant bit to maintain consistency */
}

/**
 * @brief Parses an opcode instruction and encodes the corresponding words.
 *
 * @param ptr Pointer to the string containing the opcode.
 * @param iptr Pointer to the pointer to the instruction word.
 * @param idx The index to use for encoding.
 * @param line_counter The line number of the instruction.
 * @param label_tb Pointer to the label table.
 * @param fp Pointer to the output file.
 * @return EXIT_SUCCESS on successful parsing, EXIT_FAILURE on error.
 *
 * This function parses an opcode and its operands, determining the addressing methods
 * for each operand and encoding the instruction accordingly. It also handles errors
 * related to undefined labels and unsupported addressing methods.
 */
int parseOpcode(char *ptr, unsigned short **iptr, int idx, int line_counter, label_table *label_tb, FILE *fp) {
    char str1[MAX_LABEL_SIZE + 1], str2[MAX_LABEL_SIZE + 1];
    int opr1, opr2;

    nextToken(str1, &ptr, ',');
    nextToken(str2, &ptr, ',');

    /* Check if the operands are valid labels */
    if(!checkLabel(str1, line_counter, label_tb) || !checkLabel(str2, line_counter, label_tb))
        return EXIT_FAILURE;

    opr1 = which_address_method(label_tb, NULL, str1, 0); /* 0 has no meaning */
    opr2 = which_address_method(label_tb, NULL, str2, 0); /* 0 has no meaning */

    /* Encode the extra word for the first operand */
    encode_extra_word(*iptr, idx, opr1, opr2, str1, label_tb, fp);

    /* Advance the index and instruction pointer if both operands are not using the same register */
    if(!(opr1 == -1 || (opr1 >= 2 && opr2 >= 2))) idx++, (*iptr)++;

    /* Encode the extra word for the second operand */
    encode_extra_word(*iptr, idx, opr2, -1, str2, label_tb, fp);

    /* Advance the instruction pointer if the second operand is valid */
    if(opr2 != -1) (*iptr)++;
    return EXIT_SUCCESS;
}
