#include <ctype.h>

void nextToken(char *dest, char **ptr) {
    while(*ptr && **ptr && isspace(**ptr)) (*ptr)++;
    while(*ptr && **ptr && !isspace(**ptr)) {
        *dest = **ptr;
        dest++;
        (*ptr)++;
    }
    *dest = '\0';
}
