#include <stdio.h>
#include <stdlib.h>

void allocFail(char *ptr) {
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
}

void reallocFail(char *ptr, char *new_ptr) {
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

