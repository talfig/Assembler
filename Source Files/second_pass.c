#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "globals.h"
#include "errors.h"
#include "opcode_utils.h"

int second_pass(char *file_name, label_table *label_tb, unsigned short *instructions, unsigned short *data) {
    char line[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 2], *ptr;
    int foundErr = EXIT_SUCCESS, line_counter = 0, i;
    unsigned short *iptr = instructions;
    label *lb = NULL;
    FILE *fp;

    fp = fopen(file_name, "r");
    openFail(fp);

    while((ptr = fgets(line, MAX_LINE_SIZE + 1, fp))) {
        line_counter++;

        if(*ptr == ';') continue;

        nextToken(str, &ptr, ' ');
        if(!(*str)) continue;

        /* Label found */
        if(str[strlen(str) - 1] == ':') nextToken(str, &ptr, ' ');

        /* Check for data directives, opcodes, or labels */
        if(!strcmp(str, ".data") || !strcmp(str, ".string") || !strcmp(str, ".extern")) continue;
        else if(!strcmp(str, ".entry")) {
            nextToken(str, &ptr, ' ');
            lb = find_label(label_tb, str);
            if(lb && !lb->address) {
                printf("Error: Found .entry label at line %d that is not defined in the file \n", line_counter);
                foundErr = EXIT_FAILURE;
            }
        } else if(get_opcode(str) != opcode_none) {
            iptr++;
            if(parseOpcode(ptr, &iptr, line_counter, label_tb)) {
                foundErr = EXIT_FAILURE;
                continue;
            }
        }
    }

    fclose(fp);
    if(foundErr) {
        freeLabelTable(label_tb);
        return foundErr;
    }
    for(i = 0; i < 40; i++)
        printf("%d, %d\n", i + 1, instructions[i]);
    return EXIT_SUCCESS;
}
