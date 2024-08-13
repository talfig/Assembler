#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "globals.h"
#include "errors.h"
#include "opcode_utils.h"
#include "file_utils.h"

int second_pass(char *file_name, label_table *label_tb, unsigned short *instructions, unsigned short *data, int DC) {
    char line[MAX_LINE_SIZE + 1], str[MAX_LABEL_SIZE + 2], *ptr;
    unsigned short foundErr = EXIT_SUCCESS, line_counter = 0, IC = 0;
    unsigned short *iptr = instructions;
    label *lb = NULL;
    FILE *fp_in, *fp_out, *fp_ent, *fp_ext;

    /* fix the names */
    fp_in = fopen(file_name, "r");
    openFail(fp_in);
    fp_out = fopen("encode.txt", "w");
    openFail(fp_out);
    fp_ent = fopen("ent.txt", "w");
    openFail(fp_ent);
    fp_ext = fopen("ext.txt", "w");
    openFail(fp_ext);


    while((ptr = fgets(line, MAX_LINE_SIZE + 1, fp_in))) {
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
            iptr++, IC++;
            if(parseOpcode(ptr, &iptr, IC, line_counter, label_tb, fp_ext)) {
                foundErr = EXIT_FAILURE;
                continue;
            }
            IC = iptr - instructions;
        }
    }

    fprintf(fp_out, "  %d %d\n", IC, DC);
    print_instructions(instructions, IC, fp_out);
    print_data(data, IC, DC, fp_out);
    create_entry_file(label_tb, fp_ent);

    close_multiple_files(fp_in, fp_out, fp_ent, fp_ext);

    if(!has_entry_label(label_tb))
        remove_file("ent.txt", label_tb);
    if(!has_extern_label(label_tb))
        remove_file("ext.txt", label_tb);

    freeLabelTable(label_tb);

    if(foundErr) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
