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
    char line[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 2], *ptr;
    int foundErr = EXIT_SUCCESS, line_counter = 0, IC = 0, DC = 0, extra_words;
    label_table label_tb;
    label *lb;
    opcode op;
    emptyLabelTable(&label_tb);


    /* add a . error */
    while((ptr = fgets(line, MAX_LINE_SIZE + 1, fp))) {
        line_counter++;

        if(*ptr == ';')
            continue;

        nextToken(str, &ptr, ' ');

        if(str[strlen(str) - 1] == ':') {
            str[strlen(str) - 1] = '\0';
            /* add error message */
            if(parseLabel(&label_tb, macr_tb, str, fp)) {
                foundErr = EXIT_FAILURE;
                continue;
            }

            nextToken(str, &ptr, ' ');

            if(!strcmp(str, ".data")) {
                extra_words = isLegalData(ptr);
                if(!extra_words) {
                    foundErr = EXIT_FAILURE;
                    continue;
                }
                lb = getLabelTail(&label_tb);
                lb->address = DC;
                lb->isdata = 1;
                DC += extra_words;
            } else if(!strcmp(str, ".string")) {
                extra_words = isLegalString(ptr);
                if(!extra_words) {
                    foundErr = EXIT_FAILURE;
                    continue;
                }
                lb = getLabelTail(&label_tb);
                lb->address = DC;
                lb->isdata = 1;
                DC += extra_words;
            } else if((op = get_opcode(str)) != opcode_none) {
                extra_words = isLegalOpcode(op, ptr, &label_tb, macr_tb);
                if(!extra_words) {
                    foundErr = EXIT_FAILURE;
                    continue;
                }
                lb = getLabelTail(&label_tb);
                lb->address = IC + 100;
                IC += extra_words;
            }  else if(!strcmp(str, "data") || !strcmp(str, "string")) { /* add error missing . */
                foundErr = EXIT_FAILURE;
                continue;
            } else { /* add error */
                foundErr = EXIT_FAILURE;
                continue;
            }
        }

        /* add error message */
        if(!strcmp(str, ".entry") || !strcmp(str, ".extern")) {
            nextToken(str, &ptr, ' ');
            if(parseLabel(&label_tb, macr_tb, str, fp)) {
                foundErr = EXIT_FAILURE;
                continue;
            }
        }

        if(!strcmp(str, ".data")) {
            extra_words = isLegalData(ptr);
            if(!extra_words) {
                foundErr = EXIT_FAILURE;
                continue;
            }
            DC += extra_words;
        } else if(!strcmp(str, ".string")) {
            extra_words = isLegalString(ptr);
            if(!extra_words) {
                foundErr = EXIT_FAILURE;
                continue;
            }
            DC += extra_words;
        } else if((op = get_opcode(str)) != opcode_none) {
            extra_words = isLegalOpcode(op, ptr, &label_tb, macr_tb);
            if(!extra_words) {
                foundErr = EXIT_FAILURE;
                continue;
            }
            IC += extra_words;
        } else if(  !strcmp(str, "entry") ||
                    !strcmp(str, "extern") ||
                    !strcmp(str, "data") ||
                    !strcmp(str, "string")  ) { /* add error missing . */
            foundErr = EXIT_FAILURE;
            continue;
        } else { /* add error */
            foundErr = EXIT_FAILURE;
            continue;
        }
    }
    increaseDataLabelTableAddress(&label_tb, IC + 100);

    fclose(fp);
    return foundErr;
}
