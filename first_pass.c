#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "label.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "globals.h"
#include "integer_utils.h"

int first_pass(FILE *fp) {
    char ptr[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 1], name[MAX_LABEL_SIZE + 1], *tmp;
    int foundErr = EXIT_SUCCESS, line_counter = 0, IC = 0, DC = 0;
    label_table label_tb;
    opcode op;
    emptyLabelTable(&label_tb);

    while((tmp = fgets(ptr, MAX_LINE_SIZE + 1, fp))) {
        if(*tmp == ';')
            continue;

        nextToken(str, &tmp, ' ');
        if(str[strlen(str) - 1] == ':') {
            str[strlen(str) - 1] = '\0';
            /* add error message */
            if(parseLabel(&label_tb, str, fp)) {
                foundErr = EXIT_FAILURE;
                continue;
            }

            nextToken(str, &tmp, ' ');
            if(!strcmp(str, ".data")) {
                if(!isLegalData(tmp))
                    continue;
                
            }
        }

        /* check opcode or .data or .string */
    }

    freeLabelTable(&label_tb);
    fclose(fp);
    return foundErr;
}

