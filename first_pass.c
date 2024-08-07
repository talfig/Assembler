#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "label.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "globals.h"
#include "errors.h"

int first_pass(FILE *fp, macr_table *macr_tb) {
    char ptr[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 2], name[MAX_LABEL_SIZE + 2], *tmp;
    int foundErr = EXIT_SUCCESS, line_counter = 0, IC = 0, DC = 0;
    label_table label_tb;
    opcode op;
    emptyLabelTable(&label_tb);

    while((tmp = fgets(ptr, MAX_LINE_SIZE + 1, fp))) {
        line_counter++;

        if(*tmp == ';')
            continue;

        nextToken(str, &tmp, ' ');
        if(str[strlen(str) - 1] == ':') {
            str[strlen(str) - 1] = '\0';
            /* add error message */
            if(parseLabel(&label_tb, macr_tb, str, fp)) {
                foundErr = EXIT_FAILURE;
                continue;
            }

            nextToken(str, &tmp, ' ');
            if(!strcmp(str, ".data")) {
                if(!isLegalData(tmp))
                    continue;
            }

            if(!strcmp(str, ".string")) {
                if(!isLegalString(tmp))
                    continue;
            }


        }


        /* check opcode or .data or .string */

    }

    freeMacrTable(macr_tb);
    freeLabelTable(&label_tb);
    fclose(fp);
    return foundErr;
}

