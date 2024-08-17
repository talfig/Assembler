#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"
#include "label.h"
#include "macr.h"
#include "errors_handling.h"
#include "file_utils.h"

char *append_suffix(const char *str, const char *suffix, label_table *label_tb,
                    macr_table *macr_tb, FILE *fp1, FILE *fp2, FILE *fp3) {
    size_t len1 = strlen(str);
    size_t len2 = strlen(suffix);
    char *result = (char *)malloc(len1 + len2 + 1);

    if(!result) {
        fprintf(stderr, "    %s\n", getError(ALLOC_FAILED));
        if(label_tb) freeLabelTable(label_tb);
        if(macr_tb) freeMacrTable(macr_tb);
        close_multiple_files(fp1, fp2, fp3, NULL);
        exit(EXIT_FAILURE);
    }

    sprintf(result, "%s%s", str, suffix);
    return result;
}

FILE *open_file_with_suffix(const char *file_name, const char *suffix, const char *mode,
                            label_table *label_tb, macr_table *macr_tb, FILE *fp1, FILE *fp2, FILE *fp3) {
    char *file_name_with_suffix = append_suffix(file_name, suffix, label_tb, macr_tb, fp1, fp2, fp3);
    FILE *fp = fopen(file_name_with_suffix, mode);

    /* Check if the file opening failed */
    if(!fp) {
        fprintf(stderr, "    %s %s\n", getError(FILE_OPEN_FAILED), file_name_with_suffix);
        if(label_tb) freeLabelTable(label_tb);
        if(macr_tb) freeMacrTable(macr_tb);
        free(file_name_with_suffix);
        close_multiple_files(fp1, fp2, fp3, NULL);
        exit(EXIT_FAILURE);
    }

    free(file_name_with_suffix);
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
        if(ptr->is_entry) {
            fprintf(fp, "%s ", ptr->name);
            if(ptr->address < 1000)  fprintf(fp, "0");
            fprintf(fp, "%d\n", ptr->address);
        }
        ptr = ptr->next;
    }
}

void close_multiple_files(FILE *fp1, FILE *fp2, FILE *fp3, FILE *fp4) {
    if(fp1) fclose(fp1);
    if(fp2) fclose(fp2);
    if(fp3) fclose(fp3);
    if(fp4) fclose(fp4);
}

void remove_file(const char *file_name) {
    if(remove(file_name))
        fprintf(stderr, "    %s %s\n", getError(FILE_DELETION_FAILED), file_name);
}

void process_file(const char *file_name, const char *suffix, void *label_tb) {
    char *file_name_with_suffix = append_suffix(file_name, suffix, label_tb, NULL, NULL, NULL, NULL);
    remove_file(file_name_with_suffix);
    free(file_name_with_suffix);
}

int assembler(int argc, char *argv[]) {
    int i, foundErr = 0;

    if(argc < 2) {
        fprintf(stderr, "%s\n", getError(MISSING_ARGUMENT));
        exit(EXIT_FAILURE);
    }

    for(i = 1; i < argc; i++) {
        if(preprocessor(argv[i]))
            foundErr = 1;
    }

    return foundErr;
}
