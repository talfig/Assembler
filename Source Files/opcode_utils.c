#include <stdlib.h>
#include "label.h"
#include "macr.h"
#include "integer_utils.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "opcode_utils.h"

int is0(char *str, int line_counter) {
    if(parseInstructionInt(str, line_counter) != INSTRUCTION_MAX_VALUE + 1)
        return 1;
    return 0;
}

int is1(label_table *label_tb, macr_table *macr_tb, char *str) {
    if(find_label(label_tb, str) || isLegalLabelName(label_tb, macr_tb, str))
        return 1;
    return 0;
}

int is2(char *str) {
    char *ptr = str;

    if(*ptr == '*' && get_register(ptr + 1) != regis_none)
        return 1;
    return 0;
}

int is3(char *str) {
    if(get_register(str) != regis_none)
        return 1;
    return 0;
}

int which_address_method(label_table *label_tb, macr_table *macr_tb, char *str, int line_counter) {
    if(is0(str, line_counter)) return 0;
    if(is1(label_tb, macr_tb, str)) return 1;
    if(is2(str)) return 2;
    if(is3(str)) return 3;
    return -1;
}

void encode_first_word(unsigned short *ptr, opcode op, int opr1, int opr2) {
    *ptr |= op << 11;
    if(opr1 >= 0) *ptr |= 1 << (7 + opr1);
    if(opr2 >= 0) *ptr |= 1 << (3 + opr2);
    *ptr |= 1 << 2;
}

int checkLabel(char *str, int line_counter, label_table *label_tb) {
    if(isLegalLabelName(label_tb, NULL, str)) {
        printf("Error: Found label at line %d that is not defined in the file.\n", line_counter);
        return 0;
    }
    return 1;
}

void encode_extra_word(unsigned short *ptr, int idx, int opr1, int opr2, char *str1, label_table *label_tb, FILE *fp) {
    int num;
    label *lb;
    regis rg;

    switch(opr1) {
        case 0:
            num = parseInstructionInt(str1, 0); /* 0 is just for the function */
            *ptr |= num << 3;
            *ptr |= 1 << 2;
            break;
        case 1:
            lb = find_label(label_tb, str1);
            *ptr |= lb->address << 3;
            if(lb->is_extern) {
                fprintf(fp, "%s ", lb->name);
                if(100 + idx < 1000) fprintf(fp, "0");
                fprintf(fp, "%d\n", 100 + idx);
                *ptr |= 1;
            }
            else *ptr |= 1 << 1;
            break;
        case 2:
            str1++;
            rg = get_register(str1);
            *ptr |= 1 << 2;
            if(opr2 == -1) *ptr |= rg << 3;
            else *ptr |= rg << 6;
            break;
        case 3:
            rg = get_register(str1);
            *ptr |= 1 << 2;
            if(opr2 == -1) *ptr |= rg << 3;
            else *ptr |= rg << 6;
            break;
        default:
            break;
    }
}

int parseOpcode(char *ptr, unsigned short **iptr, int idx, int line_counter, label_table *label_tb, FILE *fp) {
    char str1[MAX_LABEL_SIZE + 2], str2[MAX_LABEL_SIZE + 2];
    int opr1, opr2;

    nextToken(str1, &ptr, ',');
    nextToken(str2, &ptr, ',');

    if(!checkLabel(str1, line_counter, label_tb) || !checkLabel(str2, line_counter, label_tb))
        return EXIT_FAILURE;

    opr1 = which_address_method(label_tb, NULL, str1, 0);
    opr2 = which_address_method(label_tb, NULL, str2, 0);

    encode_extra_word(*iptr, idx, opr1, opr2, str1, label_tb, fp);
    if(!(opr1 == -1 || (opr1 >= 2 && opr2 >= 2))) idx++, (*iptr)++;
    encode_extra_word(*iptr, idx, opr2, -1, str2, label_tb, fp);

    if(opr2 != -1) (*iptr)++;
    return EXIT_SUCCESS;
}
