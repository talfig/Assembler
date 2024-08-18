/**
 * @file token_utils.h
 * @brief Header file for token extraction and string handling utilities.
 *
 * This header file declares utility functions for extracting tokens from a string and
 * handling strings enclosed in double quotes. These functions assist in parsing and
 * processing assembly source files.
 */

#ifndef TOKEN_UTILS_H
#define TOKEN_UTILS_H

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
int nextToken(char *dest, char **ptr, const char delim);

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
int nextString(char *dest, char **ptr, int line_counter);

#endif /* TOKEN_UTILS_H */
