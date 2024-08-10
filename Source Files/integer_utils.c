#include <stdio.h>
#include "integer_utils.h"

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
            printf("Error: Not an integer at line %d.\n", line_counter);
            return max + 1;
        }

        /* Converting character to integer and accumulating result */
        result = result * 10 + (*str - '0');

        /* Checking if result is within the acceptable range */
        if(sign * result < min || sign * result > max) {
            printf("Error: Number out of range at line %d.\n", line_counter);
            return max + 1;
        }
        str++;
    }

    return sign * result;
}

int parseDataInt(char *str, int line_counter) {
    return parseInt(str, DATA_MIN_VALUE, DATA_MAX_VALUE, line_counter);
}

int parseInstructionInt(char *str, int line_counter) {
    /* add a specific error */
    if(*str != '#') {

        return INSTRUCTION_MAX_VALUE + 1;
    }
    str++;
    return parseInt(str, INSTRUCTION_MIN_VALUE, INSTRUCTION_MAX_VALUE, line_counter);
}
