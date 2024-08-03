#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "preprocessor.h"

const char *getError(int error_code) {
    const char *errors[] = {
            "Failed to dynamically allocate memory",
            ".as file name is missing",
            "The file name is too long",
            "The provided file name does not exist",
            ".am file is missing",
            "The Line is too long",
            "Failed to open new file for writing",
            "Failed to open file for reading",
            "Error - macro without name definition",
            "Error - extra text after macro name definition",
            "Setting a position in a file failed",
            "endmacr with extra text",
            "Macro has more than one definition",
            "Failed to copy file during macros expansion",
            "Macros expansion in an .as file failed",
            "Macro call before declaration",
            "Illegal name for a macro",
            "Line is too long",
            "Illegal opcode",
            "Line contains extra text",
            "Illegal argument",
            "Missing argument",
            "Missing comma between argument in a command line with two arguments",
            "Label not defined in the assembly file",
            "Illegal label after .entry",
            "Illegal comma near opcode",
            "More commas than needed",
            "Comma in the wrong place",
            "Illegal char near opcode or label",
            "Illegal char",
            "Missing comma between numbers",
            "Illegal label declaration",
            "Missing ':' after label declaration",
            "Illegal register name. Use only @r1-@r7",
            "Illegal comma before opcode",
            "Data line without '. before directive",
            "Instruction '.data' line contains non-number info",
            "Comma after the last number in a '.data' line",
            "Missing '\"' after '.string'",
            "Extra text after the string end in '.string' line",
            "IC too big for word CPU word length",
            "Label definition repeats more than once",
            "Label defined as .extern and defined in file",
            "Input number in .data line is out of range",
            "Illegal data line directive",
            "Instruction '.data' line contains illegal chars or syntax error"
    };

    if (error_code < 0 || error_code >= sizeof(errors) / sizeof(errors[0]))
        return "Unknown error code";

    return errors[error_code];
}

int checkLines(char *file_name) {
    FILE *fp;
    char line[MAX_LINE_SIZE + 2];
    int foundErr = 0;

    /* Open the file in read mode */
    fp = fopen(file_name, "r");
    if(!fp) {
        fprintf(stderr, "Unable to open the file!\n");
        return EXIT_FAILURE;
    }

    /* Read each line of the file */
    while(fgets(line, MAX_LINE_SIZE + 2, fp)) {
        if(strlen(line) > MAX_LINE_SIZE) {
            foundErr = 1;
            break;
        }
    }
    if(foundErr)
        fprintf(stderr, "Found line that exceeds %d characters!\n", MAX_LINE_SIZE);

    /* Close the file */
    fclose(fp);

    return EXIT_SUCCESS;
}

void allocFail(const char *ptr, macr_table *tb, FILE *fp, FILE *fptr) { /* Add file closer */
    if(!ptr) {
        fprintf(stderr, "Memory allocation failed for name!\n");
        freeMacrTable(tb);
        fclose(fp);
        fclose(fptr);
        exit(EXIT_FAILURE);
    }
}

void openFail(FILE *fp) {
    if(!fp) {
        fprintf(stderr, "Unable to open the file!\n");
        exit(EXIT_FAILURE);
    }
}

