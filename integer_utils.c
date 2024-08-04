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

int isLegalInteger(char *str) {
    int result = 0;
    int sign = 1;

    if(*str != '#')
        return 0;
    str++;

    /* Handling negative numbers */
    if(*str == '-') {
        sign = -1;
        str++;
    }

    /* Parsing positive numbers */
    while(*str) {
        /* Checking if each character is a digit */
        if(*str < '0' || *str > '9')
            return 0;

        /* Converting character to integer and accumulating result */
        result = result * 10 + (*str - '0');

        /* Checking if result is within the acceptable range */
        if((sign * result) < MIN_VALUE || (sign * result) > MAX_VALUE)
            return 0;
        str++;
    }

    return 1;
}