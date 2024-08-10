#ifndef OPCODE_UTILS_H
#define OPCODE_UTILS_H

#include "label.h"
#include "macr.h"

int is0(char *str, int line_counter);

int is1(label_table *label_tb, macr_table *macr_tb, char *str);

int is2(char *str);

int is3(char *str);

int which_address_method(label_table *label_tb, macr_table *macr_tb, char *str, int line_counter);

void first_word(short *ptr, opcode op, int opr1, int opr2);

#endif /* OPCODE_UTILS_H */
