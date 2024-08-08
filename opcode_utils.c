#include "label.h"
#include "macr.h"
#include "integer_utils.h"

int is0(char *str) {
    if(parseInstructionInt(str) != INSTRUCTION_MAX_VALUE + 1)
        return 1;
    return 0;
}

int is1(label_table *label_tb, macr_table *macr_tb, char *str) {
    if(isLegalLabelName(label_tb, macr_tb, str))
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

int is1_2(label_table *label_tb, macr_table *macr_tb, char *str) {
    if(is1(label_tb, macr_tb, str) || is2(str))
        return 1;
    return 0;
}

int is2_3(char *str) {
    if(is2(str) || is3(str))
        return 1;
    return 0;
}

int is1_2_3(label_table *label_tb, macr_table *macr_tb, char *str) {
    if(is1_2(label_tb, macr_tb, str) || is3(str))
        return 1;
    return 0;
}

int is0_1_2_3(label_table *label_tb, macr_table *macr_tb, char *str) {
    if(is0(str) || is1_2_3(label_tb, macr_tb, str))
        return 1;
    return 0;
}
