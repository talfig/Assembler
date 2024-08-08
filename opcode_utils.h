#ifndef OPCODE_UTILS_H
#define OPCODE_UTILS_H

#include "label.h"
#include "macr.h"

int is0(char *str);

int is1(label_table *label_tb, macr_table *macr_tb, char *str);

int is2(char *str);

int is3(char *str);

int is1_2(label_table *label_tb, macr_table *macr_tb, char *str);

int is2_3(char *str);

int is1_2_3(label_table *label_tb, macr_table *macr_tb, char *str);

int is0_1_2_3(label_table *label_tb, macr_table *macr_tb, char *str);

#endif /* OPCODE_UTILS_H */
