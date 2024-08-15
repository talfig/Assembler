#include <stdio.h>
#include <ctype.h>
#include "token_utils.h"

int nextToken(char *dest, char **ptr, const char delim) {
    int count = 0;

    while(**ptr && (isspace(**ptr) || **ptr == delim)) {
        if(**ptr == delim)
            count++;
        (*ptr)++;
    }

    while(**ptr && !isspace(**ptr) && **ptr != delim) {
        *dest = **ptr;
        dest++;
        (*ptr)++;
    }

    *dest = '\0';
    return count;
}

int nextString(char *dest, char **ptr, int line_counter) {
    while(**ptr && isspace(**ptr)) (*ptr)++;
    if(!(**ptr)) {
        printf("Error: Missing String at line %d.\n", line_counter);
        return 1;
    } else if(**ptr != '\"') {
        printf("Error: String not properly starts with \" at line %d.\n", line_counter);
        return 1;
    }

    (*ptr)++;
    while(**ptr && **ptr != '\"') {
        if(**ptr < MIN_CHAR_VALUE || **ptr > MAX_CHAR_VALUE) {
            printf("Error: String contains invalid character at line %d.\n", line_counter);
            return 1;
        }
        *dest = **ptr;
        dest++;
        (*ptr)++;
    }
    *dest = '\0';

    if(!(**ptr)) {
        printf("Error: String not properly closed with \" at line %d.\n", line_counter);
        return 1;
    }
    (*ptr)++;

    return 0;
}
