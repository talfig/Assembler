/**
 * @file errors_handling.h
 * @brief Header file for error handling functions and definitions.
 *
 * This file defines an enumeration for various error types and declares functions for handling
 * errors related to memory allocation, file operations, and input validation.
 */

#ifndef ERRORS_HANDLING_H
#define ERRORS_HANDLING_H

#include "macr.h"
#include "label.h"
#include "globals.h"

/**
 * @brief Enum representing various types of errors that can occur.
 */
typedef enum {
    ALLOC_FAILED,                     /**< Memory allocation failed. */
    REALLOC_FAILED,                   /**< Memory reallocation failed. */
    UNRECOGNIZED_COMMAND,             /**< Unrecognized command in the input. */
    LINE_TOO_LONG,                    /**< The input line exceeds the maximum allowed length. */
    EXTRANEOUS_TEXT_AFTER_MACRO,      /**< Extraneous text found after macro name. */
    FILE_OPEN_FAILED,                 /**< Failed to open the specified file. */
    MISSING_NAME_IN_MACRO,            /**< Macro definition is missing a name. */
    NOT_INTEGER,                      /**< Expected an integer value but found something else. */
    INVALID_MACRO_NAME,               /**< Invalid macro name encountered. */
    EXTRANEOUS_TEXT_AFTER_ENDMACR,    /**< Extraneous text found after "endmacr". */
    ENTRY_LABEL_UNDEFINED,            /**< Label referenced in ".entry" directive is not defined. */
    MISSING_DOT_IN_DIRECTIVE,         /**< Directive missing the initial '.'. */
    MISSING_ARGUMENT,                 /**< Missing argument in the command. */
    MISSING_COMMA,                    /**< Comma expected but not found. */
    MULTIPLE_CONSECUTIVE_COMMAS,      /**< Multiple consecutive commas found where not allowed. */
    INVALID_LABEL,                    /**< Invalid label name or format encountered. */
    ILLEGAL_COMMA,                    /**< Illegal comma found in the input. */
    INVALID_SOURCE_OPERAND,           /**< Invalid source operand for the operation. */
    INVALID_DEST_OPERAND,             /**< Invalid destination operand for the operation. */
    UNEXPECTED_OPERAND,               /**< Unexpected operand found after expected inputs. */
    INVALID_OPERAND,                  /**< Operand is invalid for the given operation. */
    MISSING_STRING,                   /**< Expected a string but none was found. */
    EXTRANEOUS_TEXT_AFTER_STRING,     /**< Extraneous text found after the string. */
    STRING_NOT_STARTED_PROPERLY,      /**< String did not start with the expected character. */
    INVALID_CHARACTER,                /**< Invalid character found within a string or command. */
    STRING_NOT_CLOSED_PROPERLY,       /**< String was not properly closed with the expected character. */
    MEMORY_OVERFLOW,                  /**< Memory overflow detected while processing data. */
    FILE_DELETION_FAILED,             /**< File deletion failed due to an error. */
    NUMBER_OUT_OF_RANGE,              /**< Numeric value is out of the allowed range. */
    UNDEFINED_LABEL,                  /**< Label referenced but not defined. */
    MULTIPLE_MACRO_DEFINITIONS        /**< Macro has more than one definition. */
} Error;

/**
 * @brief Prints an error message corresponding to the given error code and line number.
 *
 * @param line_counter The line number where the error occurred.
 * @param err The error code representing the type of error.
 */
void printError(int line_counter, Error err);

/**
 * @brief Retrieves a human-readable error message corresponding to the given error code.
 *
 * @param error_code The code of the error to retrieve the message for.
 * @return A string representing the error message.
 */
const char *getError(int error_code);

/**
 * @brief Handles memory allocation failure by printing an error and closing files.
 *
 * @param ptr Pointer to the allocated memory. If NULL, the function will handle the failure.
 * @param tb Pointer to the macro table to be freed.
 * @param fp1 Pointer to the first file to be closed.
 * @param fp2 Pointer to the second file to be closed.
 */
void allocFail(const char *ptr, macr_table *tb, FILE *fp1, FILE *fp2);

/**
 * @brief Checks if any lines in the specified file are too long.
 *
 * @param fp The file pointer to read from.
 * @param line A pointer to the line buffer to check.
 * @param line_counter The current line number being checked.
 * @return EXIT_SUCCESS if the line is of acceptable length; otherwise, EXIT_FAILURE.
 */
int checkLine(FILE *fp, char *line, int line_counter);

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
int isLegalOpcode(opcode op, char *ptr, unsigned short *iptr, int idx, int line_counter, label_table *label_tb, macr_table *macr_tb);

/**
 * @brief Validates and processes data input, checking if it's legal and encoding it.
 *
 * @param ptr Pointer to the current position in the string being processed.
 * @param dptr Pointer to the memory location where the data will be encoded.
 * @param idx The current index in the data memory.
 * @param line_counter The line number for error reporting.
 * @return The count of valid data entries or 0 if an error occurs.
 */
int isLegalData(char *ptr, unsigned short *dptr, int idx, int line_counter);

/**
 * @brief Validates and processes string input, checking if it's legal and encoding it.
 *
 * @param ptr Pointer to the current position in the string being processed.
 * @param dptr Pointer to the memory location where the string will be encoded.
 * @param idx The current index in the data memory.
 * @param line_counter The line number for error reporting.
 * @return The length of the string if valid, or 0 if an error occurs.
 */
int isLegalString(char *ptr, unsigned short *dptr, int idx, int line_counter);

#endif /* ERRORS_HANDLING_H */
