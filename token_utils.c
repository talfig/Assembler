#include <ctype.h>

int nextToken(char *dest, char **ptr, const char delim) {
    int count = 0;

    while(**ptr && isspace(**ptr) && **ptr == delim) {
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
