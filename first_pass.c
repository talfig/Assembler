#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macr.h"
#include "label.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "globals.h"

int first_pass(FILE *fp) {
    char ptr[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 1], name[MAX_LABEL_SIZE + 1], *tmp;
    int foundErr = 0, count_op;
    label *lb;
    label_table label_tb;
    opcode op;
    instruction instruct;
    emptyLabelTable(&label_tb);
    while((tmp = fgets(ptr, MAX_LINE_SIZE + 1, fp))) {
        if(tmp[0] == ';')
            continue;
        nextToken(str, &tmp, ' ');
        if(str[strlen(str) - 1] == ':') {
            str[strlen(str) - 1] = '\0';

            /* add error message to the function and change it in the preprocessor */
            if(!isLegalLabelName(&label_tb, str)) {
                foundErr = EXIT_FAILURE;
                continue;
            }

            lb = malloc(sizeof(label));
            if(!lb) {
                fprintf(stderr, "Memory allocation failed!\n");
                fclose(fp);
                freeLabelTable(&label_tb);
                exit(EXIT_FAILURE);
            }
            lb->address = 0;
            lb->next = NULL;
            lb->info = INSTRUCTION_NONE;
            lb->name = my_strdup(str);
            if(!(lb->name)) {
                fprintf(stderr, "Memory allocation failed!\n");
                fclose(fp);
                freeLabelTable(&label_tb);
                exit(EXIT_FAILURE);
            }
            addToLabelTable(&label_tb, lb);
        }
    }

    freeLabelTable(&label_tb);
    fclose(fp);
    return foundErr;
}

