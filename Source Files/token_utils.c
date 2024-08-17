#include <stdio.h>
#include <ctype.h>
#include "token_utils.h"
#include "errors_handling.h"

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
        printError(line_counter, MISSING_STRING);
        return 1;
    } else if(**ptr != '\"') {
        printError(line_counter, STRING_NOT_STARTED_PROPERLY);
        return 1;
    }

    (*ptr)++;
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
