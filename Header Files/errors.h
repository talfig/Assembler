#ifndef ERRORS_H
#define ERRORS_H

#include "macr.h"
#include "label.h"
#include "globals.h"

typedef enum {
    ERR_MEM_ALLOC_FAILED,
    ERR_MEM_REALLOC_FAILED,
    ERR_AS_FILE_NAME_MISSING,
    ERR_MACRO_DEF_START_LINE,
    ERR_LINE_TOO_LONG,
    ERR_EXTRANEOUS_TEXT_AFTER_MACRO,
    ERR_FILE_OPEN_FAILED,
    ERR_MISSING_NAME_IN_MACRO,
    ERR_INVALID_DATA_NOT_INT,
    ERR_INVALID_MACRO_NAME,
    ERR_EXTRANEOUS_TEXT_AFTER_ENDMACR,
    ERR_ENDMACR_START_LINE,
    ERR_MACRO_MULTIPLE_DEFINITIONS,
    ERR_ILLEGAL_MACRO_NAME,
    ERR_ILLEGAL_OPCODE,
    ERR_EXTRANEOUS_TEXT_AFTER_CMD,
    ERR_ILLEGAL_ARGUMENT,
    ERR_MISSING_ARGUMENT,
    ERR_MISSING_COMMA,
    ERR_MULTIPLE_CONSECUTIVE_COMMAS,
    ERR_ILLEGAL_LABEL_DECLARATION,
    ERR_MISSING_COLON_AFTER_LABEL,
    ERR_ILLEGAL_COMMA,
    ERR_INVALID_SOURCE_OPERAND,
    ERR_INVALID_DEST_OPERAND,
    ERR_UNEXPECTED_OPERAND
} Error;

const char *getError(int error_code);

void allocFail(const char *ptr, macr_table *tb, FILE *fp_in, FILE *fp_out);

void openFail(FILE *fp);

int checkLines(char *file_name);

int isLegalOpcode(opcode op, char *ptr, unsigned short *iptr, int idx, int line_counter, label_table *label_tb, macr_table *macr_tb);

int isLegalData(char *ptr, unsigned short *dptr, int idx, int line_counter);

int isLegalString(char *ptr, unsigned short *dptr, int idx, int line_counter);

#endif /* ERRORS_H */
