/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file token_utils.c
 * @brief Utility functions for token extraction and string handling in the assembler.
 *
 * This file contains utility functions for extracting tokens from a string and handling
 * strings enclosed in quotes. These functions are used during the assembly process to
 * parse and process the assembly source files.
 */

#include <ctype.h>
#include "token_utils.h"
#include "errors_handling.h"

/**
 * @brief Extracts the next token from the input string.
 *
 * This function extracts the next token from the input string `*ptr`, delimited by the specified
 * delimiter character. It copies the token into the `dest` buffer and updates `*ptr` to point
 * to the next token or character in the input string.
 *
 * @param dest Pointer to the buffer where the extracted token will be stored.
 * @param ptr Pointer to the current position in the input string.
 * @param delim The delimiter character used to separate tokens.
 * @return int The number of delimiters encountered before the token.
 */
int nextToken(char *dest, char **ptr, const char delim) {
    int count = 0;

    /* Skip leading whitespace and delimiters */
    while(**ptr && (isspace(**ptr) || **ptr == delim)) {
        if(**ptr == delim)
            count++;
        (*ptr)++;
    }

    /* Extract the token */
    while(**ptr && !isspace(**ptr) && **ptr != delim) {
        *dest = **ptr;
        dest++;
        (*ptr)++;
    }

    *dest = '\0';
    return count;
}

/**
 * @brief Extracts a string enclosed in double quotes from the input string.
 *
 * This function extracts a string enclosed in double quotes from the input string `*ptr`.
 * It copies the string into the `dest` buffer and updates `*ptr` to point to the character
 * following the closing quote. If the string is not properly enclosed or contains invalid
 * characters, an error is reported.
 *
 * @param dest Pointer to the buffer where the extracted string will be stored.
 * @param ptr Pointer to the current position in the input string.
 * @param line_counter The line number in the source file, used for error reporting.
 * @return int Returns 0 if the string is extracted successfully, or 1 if an error occurs.
 */
int nextString(char *dest, char **ptr, int line_counter) {
    /* Skip leading whitespace */
    while(**ptr && isspace(**ptr)) (*ptr)++;
    if(!(**ptr)) {
        printError(line_counter, MISSING_STRING);
        return 1;
    } else if(**ptr != '\"') {
        printError(line_counter, STRING_NOT_STARTED_PROPERLY);
        return 1;
    }

    (*ptr)++;
    /* Extract the string */
    while(**ptr && **ptr != '\"') {
        if(!isprint(**ptr)) {
            printError(line_counter, INVALID_CHARACTER);
            return 1;
        }
        *dest = **ptr;
        dest++;
        (*ptr)++;
    }
    *dest = '\0';

    if(!(**ptr)) {
        printError(line_counter, STRING_NOT_CLOSED_PROPERLY);
        return 1;
    }
    (*ptr)++;

    return 0;
}
