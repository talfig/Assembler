#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "macr.h"
#include "errors.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "globals.h"

int isLegalName(char *name) {
    if(!name || !(*name)) return 0;
    if(!isalpha(*name)) return 0;

    if(strlen(name) > MAX_LABEL_SIZE)
        return 0;

    while(*name) {
        if(!isalnum(*name) && *name != '_')
            return 0;
        name++;
    }

    return 1;
}


/* macr_table */

void emptyMacrTable(macr_table *tb) {
    tb->head = NULL;
}

macr *getMacrTail(macr_table *tb) {
    macr *ptr = tb->head;

    if(!ptr) return NULL;

    /* Traverse the list to find the tail macr */
    while(ptr -> next) ptr = ptr->next;
    return ptr;
}

void addToMacrTable(macr_table *tb, macr *ptr) {
    macr *tmp = getMacrTail(tb);

    /* If the bucket is empty, set the new node as the head */
    if(!tmp) tb->head = ptr;
    else tmp->next = ptr; /* Otherwise, add the new node at the end of the list */
}

void freeMacrTable(macr_table *tb) {
    macr *ptr, *tmp;

    ptr = tb->head;
    while(ptr) {
        tmp = ptr;
        ptr = ptr->next;
        if(tmp->name)
            free(tmp->name);
        if(tmp->info)
            free(tmp->info);
        free(tmp);
    }
}

macr *find_macr(macr_table *tb, char *name) {
    macr *ptr = NULL;
    if(tb) ptr = tb->head;

    while(ptr) {
        if(!strcmp(name, ptr->name))
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

int isLegalMacrName(macr_table *tb, char *name) {
    opcode op = get_opcode(name);
    regis rg = get_register(name);
    instruction inst = get_instruction(name);
    macr *mcr = find_macr(tb, name);
    return  isLegalName(name) &&
            strcmp(name, "macr") &&
            strcmp(name, "endmacr") &&
            (op == opcode_none) &&
            (rg == regis_none) &&
            (inst == INSTRUCTION_NONE) &&
            (mcr == NULL);
}

char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *res = malloc(len + 1);
    if(!res) return NULL;
    strcpy(res, s);
    return res;
}

int save_macr(macr_table *tb, char *name, int line_counter, FILE *fp_in, FILE *fp_out) {
    char *info, *new_info, *ptr, line[MAX_LINE_SIZE + 1];
    int len = 0;
    macr *mcr = malloc(sizeof(macr));
    if(!mcr) {
        fprintf(stderr, "%s\n", getError(0));
        freeMacrTable(tb);
        fclose(fp_in);
        fclose(fp_out);
        exit(EXIT_FAILURE);
    }

    mcr->next = NULL;
    mcr->name = my_strdup(name);
    addToMacrTable(tb, mcr);
    allocFail(mcr->name, tb, fp_in, fp_out);

    info = malloc(0);
    allocFail(info, tb, fp_in, fp_out);

    while((ptr = fgets(line, MAX_LINE_SIZE + 1, fp_in))) {
        nextToken(name, &ptr, ' ');
        if(!strcmp(name, "endmacr")) {
            if(*ptr && !isspace(*ptr)) {
                printf("Error found in line %d: %s\n", line_counter, getError(14));
                return MACR_DEF_ERR;
            }
            break;
        } else if(strstr(ptr, "endmacr")){
            printf("Error found in line %d: %s\n", line_counter, getError(15));
            return MACR_DEF_ERR;
        }

        new_info = realloc(info, len + MAX_LINE_SIZE + 1);
        if(!new_info) {
            fprintf(stderr, "%s\n", getError(1));
            free(info);
            freeMacrTable(tb);
            fclose(fp_in);
            fclose(fp_out);
            exit(EXIT_FAILURE);
        }
        info = new_info;
        ptr = info + len;
        strcpy(ptr, line);
        len = (int)strlen(info);
    }
    mcr->info = info;
    return 0;
}
