/**
 * @file error_handling.c
 * @brief Handles error reporting, file validation, and data processing functions.
 *
 * This file contains functions for error reporting, handling file operations,
 * and validating data and strings within a specific context. The code aims to
 * ensure robust error handling and data integrity during processing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "preprocessor.h"
#include "globals.h"
#include "token_utils.h"
#include "label.h"
#include "integer_utils.h"
#include "opcode_utils.h"
#include "first_pass.h"
#include "errors_handling.h"

/**
 * @brief Retrieves the error message corresponding to an error code.
 *
 * @param error_code The code representing a specific error.
 * @return The corresponding error message as a string.
 */
const char *getError(int error_code) {
    /* Array of error messages corresponding to error codes */
    const char *errors[] = {
            "Memory allocation failed",
            "Memory reallocation failed",
            "Unrecognized command",
            "Line is too long",
            "Extraneous text after macro name",
            "Unable to open the file",
            "Missing name in macro definition",
            "Not an integer",
            "Invalid macro name",
            "Extraneous text after \"endmacr\"",
            "Label is not defined in the file",
            "Directive missing '.'",
            "Missing argument",
            "Missing comma",
            "Multiple consecutive commas",
            "Invalid label",
            "Illegal comma",
            "Invalid source operand",
            "Invalid destination operand",
            "Unexpected operand",
            "Invalid operand",
            "Missing string",
            "Extraneous text after string",
            "String not properly starting with \"",
            "String contains invalid character",
            "String not properly closed with \"",
            "Memory overflow detected",
            "Error deleting the file",
            "Number out of range",
            "Undefined label",
            "Macro has more than one definition"
    };

    /* Check if the error_code is out of bounds */
    if(error_code < 0 || error_code >= sizeof(errors) / sizeof(errors[ALLOC_FAILED]))
        return "Unknown error code";

    return errors[error_code];
}

/**
 * @brief Prints the error message along with the line number.
 *
 * @param line_counter The line number where the error occurred.
 * @param err The error code corresponding to the specific error.
 */
void printError(int line_counter, Error err) {
    /* Print the error message with the line number */
    printf("    Error found in line %d: %s\n", line_counter, getError(err));
}

/**
 * @brief Handles memory allocation failure, frees resources, and exits the program.
 *
 * @param ptr The pointer that was expected to be allocated.
 * @param tb Pointer to the macro table that needs to be freed.
 * @param fp1 Pointer to the first file to be closed.
 * @param fp2 Pointer to the second file to be closed.
 */
void allocFail(const char *ptr, macr_table *tb, FILE *fp1, FILE *fp2) {
    /* Check if the allocation failed */
    if(!ptr) {
        fprintf(stderr, "    %s\n", getError(ALLOC_FAILED));
        freeMacrTable(tb);
        fclose(fp1);
        fclose(fp2);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Cleans the current line from the file if it is too long.
 *
 * @param fp The file pointer from which to read the characters.
 */
void clean_line(FILE *fp) {
    char c;

    /* Skip to the end of the current line if it is too long */
    while((c = (char)getc(fp)) != EOF && c != '\n');
}

/**
 * @brief Checks if any lines in the specified file are too long.
 *
 * @param fp The file pointer to read from.
 * @param line A pointer to the line buffer to check.
 * @param line_counter The current line number being checked.
 * @return EXIT_SUCCESS if the line is of acceptable length; otherwise, EXIT_FAILURE.
 */
int checkLine(FILE *fp, char *line, int line_counter) {
    int len = (int)strlen(line);

    /* Check if the line length exceeds the maximum allowed size */
    if(len > MAX_LINE_SIZE || (len == MAX_LINE_SIZE && line[len - 1] != '\n')) {
        printError(line_counter, LINE_TOO_LONG);
        clean_line(fp);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Validates comma usage within a string.
 *
 * @param counter The number of commas found.
 * @param str The string being checked.
 * @param line_counter The line number where the check is performed.
 * @return 1 if an error is found, otherwise 0.
 */
int check_commas(int counter, const char *str, int line_counter) {
    /* Check for missing comma */
    if(!counter && *str) {
        printError(line_counter, MISSING_COMMA);
        return 1;
    }
    /* Check for multiple consecutive commas */
    else if(counter > 1) {
        printError(line_counter, MULTIPLE_CONSECUTIVE_COMMAS);
        return 1;
    }

    return 0;
}

/**
 * @brief Validates and processes an opcode operation, checking operands and encoding the instruction.
 *
 * @param op The opcode to validate.
 * @param ptr Pointer to the current position in the string being processed.
 * @param iptr Pointer to the memory location where the instruction will be encoded.
 * @param idx The current index in the instruction memory.
 * @param line_counter The line number for error reporting.
 * @param label_tb Pointer to the label table used for resolving addresses.
 * @param macr_tb Pointer to the macro table used for resolving macro names.
 * @return The number of memory words used by the instruction, or 0 if an error occurs.
 */
int isLegalOpcode(opcode op, char *ptr, unsigned short *iptr, int idx, int line_counter, label_table *label_tb, macr_table *macr_tb) {
    char str1[MAX_LINE_SIZE + 1], str2[MAX_LINE_SIZE + 1], str3[MAX_LINE_SIZE + 1];
    int tmp, opr1, opr2, foundErr = EXIT_SUCCESS;

    /* Retrieve the first operand */
    if(nextToken(str1, &ptr, ',')) {
        printError(line_counter, ILLEGAL_COMMA);
        return 0;
    }

    /* Retrieve the second operand */
    tmp = nextToken(str2, &ptr, ',');
    if(check_commas(tmp, str2, line_counter)) return 0;

    /* Check for any extraneous text after the second operand */
    nextToken(str3, &ptr, ' ');
    if(*str3) {
        printError(line_counter, UNEXPECTED_OPERAND);
        return 0;
    }

    /* Determine the addressing methods for the operands */
    opr1 = which_address_method(label_tb, macr_tb, str1, line_counter);
    opr2 = which_address_method(label_tb, macr_tb, str2, line_counter);

    /* Adjust operand order if only one operand is provided */
    if(opr2 == -1) opr2 = opr1, opr1 = -1;

    /* Encode the first word of the instruction if there's space in memory */
    if(idx < MEMORY_SIZE) encode_first_word(iptr, op, opr1, opr2);
    else foundErr = EXIT_FAILURE;

    /* Further adjustment of operand order if necessary */
    if(opr1 == -1) opr1 = opr2, opr2 = -1;

    /* Validate operands based on the specific opcode */
    switch(op) {
        case mov:
        case add:
        case sub:
            if(opr1 == -1) {
                printError(line_counter, INVALID_SOURCE_OPERAND);
                return 0;
            }
            if(opr2 <= 0) {
                printError(line_counter, INVALID_DEST_OPERAND);
                return 0;
            }
            if(foundErr) return foundErr;

            /* Return the number of words used based on addressing methods */
            if(opr1 >= 2 && opr2 >= 2) return 2;
            return 3;

        case cmp:
            if(opr1 == -1) {
                printError(line_counter, INVALID_SOURCE_OPERAND);
                return 0;
            }
            if(opr2 == -1) {
                printError(line_counter, INVALID_DEST_OPERAND);
                return 0;
            }
            if(foundErr) return foundErr;

            /* Return the number of words used based on addressing methods */
            if(opr1 >= 2 && opr2 >= 2) return 2;
            return 3;

        case lea:
            if(opr1 != 1) {
                printError(line_counter, INVALID_SOURCE_OPERAND);
                return 0;
            }
            if(opr2 <= 0) {
                printError(line_counter, INVALID_DEST_OPERAND);
                return 0;
            }
            if(foundErr) return foundErr;
            return 3;

        case clr:
        case not:
        case inc:
        case dec:
        case red:
            /* Single operand instructions */
            if(opr1 <= 0) {
                printError(line_counter, INVALID_OPERAND);
                return 0;
            }
            /* Ensure there is no second operand */
            if(*str2) {
                printError(line_counter, UNEXPECTED_OPERAND);
                return 0;
            }
            if(foundErr) return foundErr;
            return 2;

        case jmp:
        case bne:
        case jsr:
            /* instructions with one operand */
            if(opr1 <= 0 || opr1 == 3) {
                printError(line_counter, INVALID_OPERAND);
                return 0;
            }
            /* Ensure there is no second operand */
            if(*str2) {
                printError(line_counter, UNEXPECTED_OPERAND);
                return 0;
            }
            if(foundErr) return foundErr;
            return 2;

        case prn:
            /* instruction with one operand */
            if(opr1 == -1) {
                printError(line_counter, INVALID_OPERAND);
                return 0;
            }
            /* Ensure there is no second operand */
            if(*str2) {
                printError(line_counter, UNEXPECTED_OPERAND);
                return 0;
            }
            if(foundErr) return foundErr;
            return 2;

        case rts:
        case stop:
            /* No operand instructions */
            if(*str1) {
                printError(line_counter, UNEXPECTED_OPERAND);
                return 0;
            }
            if(foundErr) return foundErr;
            return 1;

        default:
            return 0; /* Return 0 for unsupported opcodes */
    }
}

/**
 * @brief Validates and processes a data string.
 *
 * @param ptr The pointer to the data string.
 * @param dptr Pointer to where the processed data will be stored.
 * @param idx The current index in the data memory.
 * @param line_counter The line number for error reporting.
 * @return The number of data elements processed, or 0 if an error occurs.
 */
int isLegalData(char *ptr, unsigned short *dptr, int idx, int line_counter) {
    int num, countData = 0;
    char str[MAX_LINE_SIZE + 1];
    int tmp, len;

    /* Check for the first token in the string */
    if(nextToken(str, &ptr, ',')) {
        printError(line_counter, ILLEGAL_COMMA);
        return 0;
    }

    /* Iterate through each token */
    while(*str && idx < MEMORY_SIZE) {
        num = parseDataInt(str, line_counter);
        countData++;

        /* Check if the token is a valid integer */
        if(num == DATA_MAX_VALUE + 1) return 0;

        /* Validate the length of the integer */
        len = (int)strlen(str);
        if(*str == '+') len--;
        if(len != countDigits(num)) {
            printError(line_counter, NOT_INTEGER);
            return 0;
        }

        *dptr = num;        /* Store the number in the data pointer */
        *dptr &= CLEAR_MSB; /* Clear the most significant bit */
        if(++idx < MEMORY_SIZE) dptr++;

        /* Move to the next token */
        tmp = nextToken(str, &ptr, ',');
        if(check_commas(tmp, str, line_counter)) return 0; /* Check for comma errors */
    }

    /* Check for memory overflow */
    if(idx >= MEMORY_SIZE) return 0;
    return countData; /* Return the number of data elements processed */
}

/**
 * @brief Copies a string to a destination memory location as ASCII values.
 *
 * @param dest The destination pointer where the ASCII values will be stored.
 * @param source The source string to be copied.
 * @param idx The current index in the memory.
 * @return 0 if successful, 1 if memory overflow occurs.
 */
int strcpy_ascii(unsigned short *dest, char *source, int idx) {
    /* Copy each character to the destination memory */
    while(*source && idx < MEMORY_SIZE) {
        *dest = (unsigned short)*source; /* Convert character to unsigned short */
        *dest &= CLEAR_MSB;              /* Clear the most significant bit */
        if(++idx < MEMORY_SIZE) dest++;
        source++;
    }
    /* Check for memory overflow */
    if(idx >= MEMORY_SIZE) return 1;

    *dest = '\0'; /* Null-terminate the destination string */
    return 0;
}

/**
 * @brief Validates and processes a string directive.
 *
 * @param ptr The pointer to the string directive.
 * @param dptr Pointer to where the processed string will be stored.
 * @param idx The current index in the memory.
 * @param line_counter The line number for error reporting.
 * @return The length of the string if valid, otherwise 0.
 */
int isLegalString(char *ptr, unsigned short *dptr, int idx, int line_counter) {
    char str[MAX_LINE_SIZE + 1];
    int len;

    /* Retrieve the string from the pointer */
    if(nextString(str, &ptr, line_counter)) return 0;

    len = (int)strlen(str); /* Get the length of the string */
    if(strcpy_ascii(dptr, str, idx)) return 0; /* Copy the string to memory */

    nextToken(str, &ptr, ' ');
    /* Ensure there are no additional tokens after the string */
    if(*str) {
        printError(line_counter, EXTRANEOUS_TEXT_AFTER_STRING);
        return 0;
    }

    return len + 1; /* Return the length of the string plus 1, for the null terminator */
}
