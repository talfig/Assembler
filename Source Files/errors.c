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
#include "file_utils.h"
#include "errors.h"

const char *getError(int error_code) {
    const char *errors[] = {
            "Memory allocation failed",
            "Memory reallocation failed",
            ".as file name is missing",
            "macro definition after the start of the line",
            "The Line is too long",
            "Extraneous text after macro name",
            "Unable to open the file",
            "Missing name in macro definition",
            "Invalid data - not an integer",
            "Invalid macro name",
            "Extraneous text after \"endmacr\"",
            "\"endmacr\" after the start of the line",
            "Macro has more than one definition",
            "Illegal name for a macro",
            "Illegal opcode",
            "Extraneous text after end of command",
            "Illegal argument",
            "Missing argument",
            "Missing comma",
            "Multiple consecutive commas",
            "Illegal label declaration",
            "Missing ':' after label declaration",
            "Illegal comma",
            "Invalid source operand",
            "Invalid destination operand",
            "Unexpected operand"
    };

    if(error_code < 0 || error_code >= sizeof(errors) / sizeof(errors[0]))
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
    fp = open_file_with_suffix(file_name, ".as", "r", NULL, NULL);
    
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

int isLegalOpcode(opcode op, char *ptr, unsigned short *iptr, int idx, int line_counter, label_table *label_tb, macr_table *macr_tb) {
    char str1[MAX_LABEL_SIZE + 2], str2[MAX_LABEL_SIZE + 2], str3[MAX_LABEL_SIZE + 2];
    int tmp, opr1, opr2, foundErr = EXIT_SUCCESS;

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
    if(idx < MEMORY_SIZE) encode_first_word(iptr, op, opr1, opr2);
    else foundErr = EXIT_FAILURE;
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
            if(foundErr) return foundErr;
            if(opr1 >= 2 && opr2 >= 2) return 2;
            return 3;

        case cmp:
            if(opr1 == -1) {
                printf("Error: Invalid source operand at line %d.\n", line_counter);
                return 0;
            } if(opr2 == -1) {
                printf("Error: Invalid destination operand at line %d.\n", line_counter);
                return 0;
            }
            if(foundErr) return foundErr;
            if(opr1 >= 2 && opr2 >= 2) return 2;
            return 3;

        case lea:
            if(opr1 != 1) {
                printf("Error: Invalid source operand at line %d.\n", line_counter);
                return 0;
            } if(opr2 <= 0) {
                printf("Error: Invalid destination operand at line %d.\n", line_counter);
                return 0;
            }
            if(foundErr) return foundErr;
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
            if(foundErr) return foundErr;
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
            if(foundErr) return foundErr;
            return 2;

        case prn:
            if(opr1 == -1) {
                printf("Error: Invalid operand at line %d.\n", line_counter);
                return 0;
            } if(*str2) {
                printf("Error: Unexpected operand at line %d.\n", line_counter);
                return 0;
            }
            if(foundErr) return foundErr;
            return 2;

        case rts:
        case stop:
            if(*str1) {
                printf("Error: Unexpected operand at line %d.\n", line_counter);
                return 0;
            }
            if(foundErr) return foundErr;
            return 1;

        /* check if needed opcode_none */
        default:
            return 0;
    }
}



int isLegalData(char *ptr, unsigned short *dptr, int idx, int line_counter) {
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

        *dptr = num;
        *dptr &= CLEAR_MSB;
        dptr++;
        idx++;

        /* Move to the next token */
        tmp = nextToken(str, &ptr, ',');
        if(check_commas(tmp, str, line_counter)) return 0;
    }

    if(idx >= MEMORY_SIZE) return 0;
    return countData;
}

int strcpy_ascii(unsigned short *dest, char *source, int idx) {
    while(*source && idx < MEMORY_SIZE) {
        *dest = (unsigned short)*source;
        *dest &= CLEAR_MSB;
        idx++;
        dest++;
        source++;
    }
    if(idx >= MEMORY_SIZE)
        return 1;
    *dest = '\0';
    return 0;
}

int isLegalString(char *ptr, unsigned short *dptr, int idx, int line_counter) {
    char str[MAX_LINE_SIZE + 1];
    int len;

    if(nextString(str, &ptr, line_counter)) {
        printf("%s\n\n", str);
        return 0;
    }

    len = (int)strlen(str);
    if(strcpy_ascii(dptr, str, idx)) return 0;

    nextToken(str, &ptr, ' ');
    /* Ensure there are no additional tokens after the string */
    if(*str) {
        printf("Error: Unexpected token after string at line %d.\n", line_counter);
        return 0;
    }

    return len;
}
