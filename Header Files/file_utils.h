#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include "label.h"

void print_instructions(unsigned short *ptr, int IC, FILE *fp);

void print_data(unsigned short *ptr, int IC, int DC, FILE *fp);

void create_entry_file(label_table *label_tb, FILE *fp);

void close_multiple_files(FILE *fp1, FILE *fp2, FILE *fp3, FILE *fp4);

void remove_file(const char *filename, label_table *label_tb);

#endif /* FILE_UTILS_H */
