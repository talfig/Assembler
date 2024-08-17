#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "macr.h"
#include "errors_handling.h"
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
            strcmp(name, "macr") != 0 &&
            strcmp(name, "endmacr") != 0 &&
            (op == unknown_opcode) &&
            (rg == unknown_register) &&
            (inst == UNKNOWN_INSTRUCTION) &&
            (mcr == NULL);
}

char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *res = (char *)malloc(len + 1);
    if(!res) return NULL;
    strcpy(res, s);
    return res;
}

int save_macr(macr_table *tb, char *name, int line_counter, FILE *fp1, FILE *fp2) {
    char *info, *new_info, *ptr, line[MAX_LINE_SIZE + 2];
    int len = 0, foundErr = EXIT_SUCCESS;
    macr *mcr = (macr *)malloc(sizeof(macr));
    if(!mcr) {
        fprintf(stderr, "    %s\n", getError(ALLOC_FAILED));
        freeMacrTable(tb);
        fclose(fp1);
        fclose(fp2);
        exit(EXIT_FAILURE);
    }

    mcr->next = NULL;
    mcr->name = my_strdup(name);
    addToMacrTable(tb, mcr);
    allocFail(mcr->name, tb, fp1, fp2);

    info = (char *)malloc(0);
    allocFail(info, tb, fp1, fp2);

    while((ptr = fgets(line, MAX_LINE_SIZE + 2, fp1))) {
        line_counter++;
        if(checkLine(fp1, line, line_counter)) foundErr = EXIT_FAILURE;

        nextToken(name, &ptr, ' ');
        if(!strcmp(name, "endmacr")) {
            if(*ptr && !isspace(*ptr)) {
                printError(line_counter, EXTRANEOUS_TEXT_AFTER_ENDMACR);
                return EXIT_FAILURE;
            }
            break;
        }

        new_info = (char *)realloc(info, len + MAX_LINE_SIZE + 1);
        if(!new_info) {
            fprintf(stderr, "    %s\n", getError(REALLOC_FAILED));
            free(info);
            freeMacrTable(tb);
            fclose(fp1);
            fclose(fp2);
            exit(EXIT_FAILURE);
        }
        info = new_info;
        ptr = info + len;
        strcpy(ptr, line);
        len = (int)strlen(info);
    }
    mcr->info = info;

    if(foundErr) return EXIT_FAILURE;
    return line_counter;
}
