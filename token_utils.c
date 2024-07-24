#include <ctype.h>
#include <stdlib.h>

void nextToken(char *dest, size_t dest_size, char **ptr) {
    size_t i = 0;

    if(dest_size < 1) return;
    while(**ptr && isspace(**ptr))
        (*ptr)++;

    while(**ptr && !isspace(**ptr) && i < dest_size - 1) {
        dest[i] = **ptr;
        i++;
        (*ptr)++;
    }

    dest[i] = '\0';
}
