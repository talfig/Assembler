#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "preprocessor.h"
#include "globals.h"
#include "token_utils.h"
#include "label.h"
#include "integer_utils.h"
#include "opcode_utils.h"
#include "first_pass.h"

const char *getError(int error_code) {
    const char *errors[] = {
            "Memory allocation failed",
            "Memory reallocation failed",
            ".as file name is missing",
            "The file name is too long",
            "The provided file name does not exist",
            "macro definition after the start of the line",
            ".am file is missing",
            "The Line is too long",
            "Extraneous text after macro name",
            "Unable to open the file",
            "Failed to open file for reading",
            "Missing name in macro definition",
            "Invalid data - not an integer",
            "Invalid macro name",
            "Setting a position in a file failed",
            "Extraneous text after \"endmacr\"",
            "\"endmacr\" after the start of the line",
            "Macro has more than one definition",
            "Failed to copy file during macros expansion",
            "Macros expansion in an .as file failed",
            "Macro call before declaration",
            "Illegal name for a macro",
            "Line is too long",
            "Illegal opcode",
            "Extraneous text after end of command",
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
            "Missing comma",
            "Multiple consecutive commas",
            "Illegal label declaration",
            "Missing ':' after label declaration",
            "Illegal register name. Use only @r1-@r7",
            "Illegal comma",
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

void allocFail(const char *ptr, macr_table *tb, FILE *fp_in, FILE *fp_out) { /* Add file closer */
    if(!ptr) {
        fprintf(stderr, "%s\n", getError(0));
        freeMacrTable(tb);
        fclose(fp_in);
        fclose(fp_out);
        exit(EXIT_FAILURE);
    }
}

void openFail(FILE *fp) {
    if(!fp) {
        fprintf(stderr, "%s\n", getError(6));
        exit(EXIT_FAILURE);
    }
}

int checkLines(char *file_name) {
    FILE *fp;
    char line[MAX_LINE_SIZE + 2];
    int foundErr = EXIT_SUCCESS, line_counter = 0, len;

    /* Open the file in read mode */
    fp = fopen(file_name, "r");
    if(!fp) {
        fprintf(stderr, "%s\n", getError(6));
        return EXIT_FAILURE;
    }

    /* Read each line of the file */
    while(fgets(line, MAX_LINE_SIZE + 2, fp)) {
        len = (int)strlen(line);

        if(len > MAX_LINE_SIZE || (len == MAX_LINE_SIZE && line[len - 1] != '\n')) {
            printf("Error found in line %d: %s\n", line_counter, getError(5));
            foundErr = EXIT_FAILURE;
        }
    }

    /* Close the file */
    fclose(fp);
    return foundErr;
}

int check_commas(int counter, const char *str, int line_counter) {
    if(!counter && *str) {
        printf("Error: Missing comma at line %d.\n", line_counter);
        return 1;
    }
    else if(counter > 1) {
        printf("Error: Multiple consecutive commas at line %d.\n", line_counter);
        return 1;
    }

    return 0;
}

int isLegalOpcode(opcode op, char *ptr, short *iptr, int line_counter, label_table *label_tb, macr_table *macr_tb) {
    char str1[MAX_LABEL_SIZE + 2], str2[MAX_LABEL_SIZE + 2], str3[MAX_LABEL_SIZE + 2];
    int tmp, opr1, opr2;

    if(nextToken(str1, &ptr, ',')) {
        printf("Error: Illegal comma at line %d.\n", line_counter);
        return 0;
    }
    tmp = nextToken(str2, &ptr, ',');
    if(check_commas(tmp, str2, line_counter)) return 0;

    nextToken(str3, &ptr, ' ');
    if(*str3) {
        printf("Error: Unexpected third operand at line %d.\n", line_counter);
        return 0;
    }

    opr1 = which_address_method(label_tb, macr_tb, str1, line_counter);
    opr2 = which_address_method(label_tb, macr_tb, str2, line_counter);
    if(opr2 == -1) opr2 = opr1, opr1 = -1;
    first_word(iptr, op, opr1, opr2);
    if(opr1 == -1) opr1 = opr2, opr2 = -1;
    switch(op) {
        case mov:
        case add:
        case sub:
            if(opr1 == -1) {
                printf("Error: Invalid first operand at line %d.\n", line_counter);
                return 0;
            } if(opr2 <= 0) {
                printf("Error: Invalid second operand at line %d.\n", line_counter);
                return 0;
            }

            if(opr1 <= 3 && opr1 >= 2 && opr2 <= 3 && opr2 >= 2) return 2;
            return 3;

        case cmp:
            if(opr1 == -1) {
                printf("Error: Invalid first operand at line %d.\n", line_counter);
                return 0;
            } if(opr2 == -1) {
                printf("Error: Invalid second operand at line %d.\n", line_counter);
                return 0;
            }

            if(opr1 <= 3 && opr1 >= 2 && opr2 <= 3 && opr2 >= 2) return 2;
            return 3;

        case lea:
            if(opr1 == -1) {
                printf("Error: Invalid source operand at line %d.\n", line_counter);
                return 0;
            } if(opr2 <= 0) {
                printf("Error: Source operand must be a label at line %d.\n", line_counter);
                return 0;
            }

            return 3;

        case clr:
        case not:
        case inc:
        case dec:
        case red:
            if(opr1 <= 0) {
                printf("Error: Invalid operand at line %d.\n", line_counter);
                return 0;
            } if(*str2) {
                printf("Error: Unexpected operand at line %d.\n", line_counter);
                return 0;
            }

            return 2;

        case jmp:
        case bne:
        case jsr:
            if(opr1 <= 0 || opr1 == 3) {
                printf("Error: Invalid jump operand at line %d.\n", line_counter);
                return 0;
            } if(*str2) {
                printf("Error: Unexpected operand at line %d.\n", line_counter);
                return 0;
            }

            return 2;

        case prn:
            if(opr1 == -1) {
                printf("Error: Invalid operand at line %d.\n", line_counter);
                return 0;
            } if(*str2) {
                printf("Error: Unexpected operand at line %d.\n", line_counter);
                return 0;
            }

            return 2;

        case rts:
        case stop:
            if(*str1) {
                printf("Error: Unexpected operand at line %d.\n", line_counter);
                return 0;
            }

            return 1;

        /* check if needed opcode_none */
        default:
            printf( "Error: Invalid opcode case at line %d.\n", line_counter);
            return 0;
    }
}



int isLegalData(char *ptr, short *dptr, short idx, int line_counter) {
    int num, countData = 0;
    char str[DATA_MAX_SIZE + 1];
    int tmp, len;

    /* Check for the first token in the string */
    if(nextToken(str, &ptr, ',')) {
        printf("Error: Illegal comma at line %d.\n", line_counter);
        return 0;
    }

    /* Iterate through each token */
    while(*str && idx < MEMORY_SIZE) {
        num = parseDataInt(str, line_counter);
        countData++;

        /* Check if the token is a valid integer */
        if(num == DATA_MAX_VALUE + 1) return 0;

        /* Validate the length of the integer */
        len = (int)strlen(str);
        if(*str == '+') len--;
        if(len != countDigits(num)) {
            printf("Error found in line %d: Not an integer \n", line_counter);
            return 0;
        }

        *dptr = (short)num;
        dptr++;
        idx++;

        /* Move to the next token */
        tmp = nextToken(str, &ptr, ',');
        if(check_commas(tmp, str, line_counter)) return 0;
    }

    if(idx >= MEMORY_SIZE) {
        printf("Error: Out of memory.\n");
        return 0;
    }

    return countData;
}

int strcpy_ascii(short *dest, char *source, short idx) {
    while(*source && idx < MEMORY_SIZE) {
        *dest = (short)*source;
        idx++;
        dest++;
        source++;
    }
    if(idx >= MEMORY_SIZE)
        return 1;
    *dest = '\0';
    return 0;
}

int isLegalString(char *ptr, short *dptr, short idx, int line_counter) {
    char str[MAX_LINE_SIZE + 1];
    int len;

    nextToken(str, &ptr, ' ');
    len = (int)strlen(str) - 2;

    /* Check if the string is properly enclosed in double quotes */
    if(str[0] != '\"' || str[strlen(str) - 1] != '\"') {
        printf("Error: String not properly enclosed in double quotes at line %d.\n", line_counter);
        return 0;
    }
    str[strlen(str) - 1] = '\0';
    if(strcpy_ascii(dptr, str + 1, idx)) {
        printf("Error: Out of memory.\n");
        return 0;
    }

    nextToken(str, &ptr, ' ');

    /* Ensure there are no additional tokens after the string */
    if(*str) {
        printf("Error: Unexpected token after string at line %d.\n", line_counter);
        return 0;
    }

    return len;
}
