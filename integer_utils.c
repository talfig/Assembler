#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "integer_utils.h"
#include "token_utils.h"

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

int parseInt(char *str, int min, int max) {
    int result = 0;
    int sign = 1;

    /* Handling negative numbers */
    if(*str == '-') {
        sign = -1;
        str++;
    }

    /* Parsing positive numbers */
    while(*str) {
        /* Checking if each character is a digit */
        if(*str < '0' || *str > '9')
            return max + 1;

        /* Converting character to integer and accumulating result */
        result = result * 10 + (*str - '0');

        /* Checking if result is within the acceptable range */
        if(sign * result < min || sign * result > max)
            return max + 1;
        str++;
    }

    return sign * result;
}

int parseDataInt(char *str) {
    if(!isspace(*str) && *str != '+' && *str != '-')
        return DATA_MAX_VALUE + 1;
    return parseInt(str, DATA_MIN_VALUE, DATA_MAX_VALUE);
}

int parseInstructionInt(char *str) {
    if(*str != '#')
        return INSTRUCTION_MAX_VALUE + 1;
    str++;
    return parseInt(str, INSTRUCTION_MIN_VALUE, INSTRUCTION_MAX_VALUE);
}


int isLegalData(char *ptr) {
    int num, isLegal = 1;
    char str[DATA_MAX_SIZE + 1];

    /* Check for the first token in the string */
    if(nextToken(str, &ptr, ',')) return 0;

    /* Iterate through each token */
    while(*ptr) {
        num = parseDataInt(ptr);

        /* Check if the token is a valid integer */
        if(num == DATA_MAX_VALUE + 1) return 0;

        /* Validate the length of the integer */
        else if(strlen(ptr) != countDigits(num)) {
            printf("Invalid number - not an integer\n");
            return 0;
        }

        /* Move to the next token */
        else if(nextToken(str, &ptr, ',') != 1) return 0;
    }

    /* Final validation of the format */
    if(*str) {
        printf("Extraneous text after end of command\n");
        isLegal = 0;
    }

    return isLegal;
}
