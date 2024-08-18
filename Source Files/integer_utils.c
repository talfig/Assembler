#include "integer_utils.h"
#include "errors_handling.h"

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

int parseDataInt(char *str, int line_counter) {
    return parseInt(str, DATA_MIN_VALUE, DATA_MAX_VALUE, line_counter);
}

int parseInstructionInt(char *str, int line_counter) {
    if(*str != '#') return INSTRUCTION_MAX_VALUE + 1;
    return parseInt(str + 1, INSTRUCTION_MIN_VALUE, INSTRUCTION_MAX_VALUE, line_counter);
}
