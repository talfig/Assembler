/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file integer_utils.c
 * @brief Contains utility functions for handling integers.
 *
 * This file includes error handling for invalid inputs.
 */

#include "integer_utils.h"
#include "errors_handling.h"

/**
 * @brief Counts the number of digits in an integer.
 *
 * @param num The integer whose digits are to be counted.
 * @return The number of digits in the integer.
 */
int countDigits(int num) {
    int count = 0;

    /* If the number is negative or zero, it adds one digit */
    if(num <= 0) count++;

    /* Counting digits by continuously dividing by 10 until num is equal to 0 */
    while(num) {
        num /= 10;
        count++;
    }
    return count;
}

/**
 * @brief Parses a string to an integer with range validation.
 *
 * This function parses a string representation of an integer.
 * It also prints an error message if the string is not a valid integer or if the result is out of range.
 *
 * @param str The string containing the integer representation.
 * @param min The minimum acceptable value for the integer.
 * @param max The maximum acceptable value for the integer.
 * @param line_counter The line number for error reporting.
 * @return The parsed integer value, or max + 1 if there is an error.
 */
int parseInt(char *str, int min, int max, int line_counter) {
    int result = 0;
    int sign = 1;

    /* Handling negative numbers */
    if(*str == '+') str++;
    else if(*str == '-') {
        sign = -1;
        str++;
    }

    /* Parsing positive numbers */
    while(*str) {
        /* Checking if each character is a digit */
        if(*str < '0' || *str > '9') {
            printError(line_counter, NOT_INTEGER);
            return max + 1;
        }

        /* Converting character to integer and accumulating result */
        result = result * 10 + (*str - '0');

        /* Checking if result is within the acceptable range */
        if(sign * result < min || sign * result > max) {
            printError(line_counter, NUMBER_OUT_OF_RANGE);
            return max + 1;
        }
        str++;
    }

    return sign * result;
}

/**
 * @brief Parses a string to an integer with data-specific range validation.
 *
 * @param str The string containing the integer representation.
 * @param line_counter The line number for error reporting.
 * @return The parsed integer value, or DATA_MAX_VALUE + 1 if there is an error.
 */
int parseDataInt(char *str, int line_counter) {
    return parseInt(str, DATA_MIN_VALUE, DATA_MAX_VALUE, line_counter);
}

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
int parseInstructionInt(char *str, int line_counter) {
    if(*str != '#') return INSTRUCTION_MAX_VALUE + 1;
    return parseInt(str + 1, INSTRUCTION_MIN_VALUE, INSTRUCTION_MAX_VALUE, line_counter);
}
