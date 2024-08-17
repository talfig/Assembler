#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include "label.h"

char *append_suffix(const char *str, const char *suffix, label_table *label_tb,
                    macr_table *macr_tb, FILE *fp1, FILE *fp2, FILE *fp3);

FILE *open_file_with_suffix(const char *file_name, const char *suffix, const char *mode,
                            label_table *label_tb, macr_table *macr_tb, FILE *fp1, FILE *fp2, FILE *fp3);

void print_instructions(unsigned short *ptr, int IC, FILE *fp);

void print_data(unsigned short *ptr, int IC, int DC, FILE *fp);

void create_entry_file(label_table *label_tb, FILE *fp);

void close_multiple_files(FILE *fp1, FILE *fp2, FILE *fp3, FILE *fp4);

void remove_file(const char *file_name);

void process_file(const char *file_name, const char *suffix, void *label_tb);

int assembler(int argc, char *argv[]);

#endif /* FILE_UTILS_H */
