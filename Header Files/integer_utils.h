/**
 * @file integer_utils.h
 * @brief Header file for integer utility functions.
 *
 * This header file declares utility functions and constants for handling integers.
 */

#ifndef INTEGER_UTILS_H
#define INTEGER_UTILS_H

/**
 * @def DATA_MAX_VALUE
 * @brief Maximum value for data integers.
 */
#define DATA_MAX_VALUE 16383

/**
 * @def DATA_MIN_VALUE
 * @brief Minimum value for data integers.
 */
#define DATA_MIN_VALUE (-16384)

/**
 * @def INSTRUCTION_MAX_VALUE
 * @brief Maximum value for instruction integers.
 */
#define INSTRUCTION_MAX_VALUE 2047

/**
 * @def INSTRUCTION_MIN_VALUE
 * @brief Minimum value for instruction integers.
 */
#define INSTRUCTION_MIN_VALUE (-2048)

/**
 * @brief Counts the number of digits in an integer.
 *
 * @param num The integer whose digits are to be counted.
 * @return The number of digits in the integer.
 */
int countDigits(int num);

/**
 * @brief Parses a string to an integer with data-specific range validation.
 *
 * @param str The string containing the integer representation.
 * @param line_counter The line number for error reporting.
 * @return The parsed integer value, or DATA_MAX_VALUE + 1 if there is an error.
 */
int parseDataInt(char *str, int line_counter);

/**
 * @brief Parses a string to an integer for instruction-specific values.
 *
 * This function parses a string representing an instruction integer and
 * ensuring it starts with '#'.
 *
 * @param str The string containing the integer representation, prefixed with '#'.
 * @param line_counter The line number for error reporting.
 * @return The parsed integer value, or INSTRUCTION_MAX_VALUE + 1 if there is an error.
 */
int parseInstructionInt(char *str, int line_counter);

#endif /* INTEGER_UTILS_H */
