#include "stdio.h"
#include "label.h"

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
