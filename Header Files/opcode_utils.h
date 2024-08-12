#ifndef OPCODE_UTILS_H
#define OPCODE_UTILS_H

#include "label.h"
#include "macr.h"

int which_address_method(label_table *label_tb, macr_table *macr_tb, char *str, int line_counter);

void encode_first_word(unsigned short *ptr, opcode op, int opr1, int opr2);

int parseOpcode(char *ptr, unsigned short **iptr, int line_counter, label_table *tb);

#endif /* OPCODE_UTILS_H */
