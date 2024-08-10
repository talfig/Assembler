#include "label.h"
#include "macr.h"
#include "integer_utils.h"

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

void first_word(short *ptr, opcode op, int opr1, int opr2) {
    *ptr |= op << 11;
    if(opr1 >= 0) *ptr |= 1 << (7 + opr1);
    if(opr2 >= 0) *ptr |= 1 << (3 + opr2);
    *ptr |= 1 << 2;
}
