#include <stdio.h>
#include <stdlib.h>

void allocFail(char *ptr) { /* Add file closer */
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
}

void reallocFail(char *ptr, char *new_ptr) { /* Add file closer */
    if(!new_ptr) {
        fprintf(stderr, "Memory reallocation failed!\n");
        free(ptr);
        exit(EXIT_FAILURE);
    }
}

void openFail(FILE *fp) {
    if (!fp) {
        fprintf(stderr, "Unable to open the file!\n");
        exit(EXIT_FAILURE);
    }
}

