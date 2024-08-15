#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"
#include "label.h"
#include "macr.h"
#include "errors.h"

char *append_suffix(const char *str, const char *suffix, label_table *label_tb, macr_table *macr_tb) {
    size_t len1 = strlen(str);
    size_t len2 = strlen(suffix);
    char* result = (char*)malloc(len1 + len2 + 1);

    if(!result) {
        fprintf(stderr, "Memory allocation failed.\n");
        if(label_tb) freeLabelTable(label_tb);
        if(macr_tb) freeMacrTable(macr_tb);
        exit(EXIT_FAILURE);
    }

    sprintf(result, "%s%s", str, suffix);

    return result;
}

FILE* open_file_with_suffix(const char* file_name, const char* suffix, const char* mode, label_table *label_tb, macr_table *macr_tb) {
    char* file_name_with_suffix = append_suffix(file_name, suffix, label_tb, macr_tb);
    FILE* fp = fopen(file_name_with_suffix, mode);
    free(file_name_with_suffix);
    openFail(fp);
    return fp;
}

void print_instructions(unsigned short *ptr, int IC, FILE *fp) {
    int i;

    for(i = 0; i < IC; i++) {
        if(i < 1000)  fprintf(fp, "0");
        fprintf(fp, "%d ", 100 + i);
        fprintf(fp, "%05o\n", ptr[i]);
    }
}

void print_data(unsigned short *ptr, int IC, int DC, FILE *fp) {
    int i;

    for(i = 0; i < DC; i++) {
        if(i < 1000)  fprintf(fp, "0");
        fprintf(fp, "%d ", 100 + IC + i);
        fprintf(fp, "%05o\n", ptr[i]);
    }
}

void create_entry_file(label_table *label_tb, FILE *fp) {
    label *ptr = label_tb->head;

    while(ptr) {
        if(ptr->is_entry)
            fprintf(fp, "%s %d\n", ptr->name, ptr->address);
        ptr = ptr->next;
    }
}

void close_multiple_files(FILE *fp1, FILE *fp2, FILE *fp3, FILE *fp4) {
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}

void remove_file(const char *filename, label_table *label_tb, macr_table *macr_tb) {
    if(remove(filename)) {
        if(label_tb) freeLabelTable(label_tb);
        if(macr_tb) freeMacrTable(macr_tb);
        fprintf(stderr, "Error deleting the file");
    }
}

int assembler(int argc, char *argv[]) {
    int i, foundErr = 0;

    if(argc < 2) {
        fprintf(stderr, "Not enough arguments were given.\n");
        exit(EXIT_FAILURE);
    }

    for(i = 1; i < argc; i++) {
        if(preprocessor(argv[i]))
            foundErr = 1;
    }

    return foundErr;
}
