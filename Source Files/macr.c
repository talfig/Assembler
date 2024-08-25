/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file macr.c
 * @brief Contains functions for managing macro definitions in an assembler.
 *
 * This file includes functions to handle macro tables, check the legality of macro names,
 * and manage memory related to macros. It provides functionalities for adding, finding,
 * and freeing macros, as well as saving macro information from files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "macr.h"
#include "errors_handling.h"
#include "preprocessor.h"
#include "token_utils.h"
#include "globals.h"

/**
 * @brief Checks if a given name is a legal macro name.
 *
 * A legal macro name starts with an alphabetic character and contains only alphanumeric
 * characters or underscores. It must not exceed MAX_LABEL_SIZE.
 *
 * @param name The name to be checked.
 * @return 1 if the name is legal, 0 otherwise.
 */
int isLegalName(char *name) {
    if(!name || !(*name)) return 0;  /* Check if the name is NULL or empty */
    if(!isalpha(*name)) return 0;    /* Check if the first character is alphabetic */

    if(strlen(name) > MAX_LABEL_SIZE)
        return 0;  /* Check if the length of the name exceeds the maximum allowed size */

    while(*name) {
        if(!isalnum(*name) && *name != '_')
            return 0;  /* Check if the name contains only valid characters */
        name++;
    }

    return 1;
}

/**
 * @brief Initializes a macro table by setting its head to NULL.
 *
 * @param tb Pointer to the macro table to be initialized.
 */
void initMacrTable(macr_table *tb) {
    tb->head = NULL;
}

/**
 * @brief Gets the tail macro from a macro table.
 *
 * @param tb Pointer to the macro table.
 * @return Pointer to the last macro in the table, or NULL if the table is empty.
 */
macr *getMacrTail(macr_table *tb) {
    macr *ptr = tb->head;

    if(!ptr) return NULL;  /* If the table is empty, return NULL */

    /* Traverse the list to find the tail macro */
    while(ptr -> next) ptr = ptr->next;
    return ptr;
}

/**
 * @brief Adds a macro to the macro table.
 *
 * @param tb Pointer to the macro table.
 * @param ptr Pointer to the macro to be added.
 */
void addToMacrTable(macr_table *tb, macr *ptr) {
    macr *tmp = getMacrTail(tb);

    /* If the table is empty, set the new macro as the head */
    if(!tmp) tb->head = ptr;
    else tmp->next = ptr;  /* Otherwise, add the new macro at the end of the list */
}

/**
 * @brief Frees all macros in the macro table and releases associated memory.
 *
 * @param tb Pointer to the macro table to be freed.
 */
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

/**
 * @brief Finds a macro by name in the macro table.
 *
 * @param tb Pointer to the macro table.
 * @param name The name of the macro to find.
 * @return Pointer to the macro if found, or NULL if not found.
 */
macr *find_macr(macr_table *tb, char *name) {
    macr *ptr = NULL;
    if(tb) ptr = tb->head;

    while(ptr) {
        if(!strcmp(name, ptr->name))
            return ptr;  /* Return the macro if the name matches */
        ptr = ptr->next;
    }
    return NULL;
}

/**
 * @brief Checks if a macro name is legal.
 *
 * A legal macro name is one that is a valid identifier, not a reserved keyword, and does not
 * conflict with existing macros, opcodes, or registers.
 *
 * @param tb Pointer to the macro table.
 * @param name The name to be checked.
 * @return 1 if the name is legal, 0 otherwise.
 */
int isLegalMacrName(macr_table *tb, char *name) {
    opcode op = get_opcode(name);
    regis rg = get_register(name);
    macr *mcr = find_macr(tb, name);
    return  isLegalName(name) &&
            strcmp(name, "macr") != 0 &&
            strcmp(name, "endmacr") != 0 &&
            (op == unknown_opcode) &&
            (rg == unknown_register) &&
            (mcr == NULL);
}

/**
 * @brief Duplicates a string by allocating memory and copying the content.
 *
 * @param s The string to be duplicated.
 * @return Pointer to the newly allocated and copied string, or NULL if memory allocation fails.
 */
char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *res = (char *)malloc(len + 1);
    if(!res) return NULL;
    strcpy(res, s);
    return res;
}

/**
 * @brief Saves macro information from a file into the macro table.
 *
 * Reads macro definitions from the provided file pointers and saves them into the macro table.
 * Handles memory allocation failures and checks for syntax errors.
 *
 * @param tb Pointer to the macro table.
 * @param name The name of the macro to save.
 * @param line_counter Counter for the current line in the file.
 * @param fp1 File pointer to read macro definitions from.
 * @param fp2 Additional file pointer for error handling.
 * @return The updated line counter if successful, or EXIT_FAILURE if an error occurs.
 */
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
    mcr->name = my_strdup(name); /* Duplicate the macro name */
    addToMacrTable(tb, mcr);
    allocFail(mcr->name, tb, fp1, fp2);

    info = (char *)malloc(0); /* Allocate initial memory for macro information */
    allocFail(info, tb, fp1, fp2);

    while((ptr = fgets(line, MAX_LINE_SIZE + 2, fp1))) {
        line_counter++;
        /* Check for syntax errors */
        if(checkLine(fp1, line, line_counter)) foundErr = EXIT_FAILURE;

        nextToken(name, &ptr, ' ');
        if(!strcmp(name, "endmacr")) {
            if(*ptr && !isspace(*ptr)) {
                printError(line_counter, EXTRANEOUS_TEXT_AFTER_ENDMACR);
                return EXIT_FAILURE;
            }
            break; /* Exit the loop if "endmacr" is encountered */
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
        strcpy(ptr, line); /* Append the new line to the macro information */
        len = (int)strlen(info); /* Update the length of the macro information */
    }
    mcr->info = info;

    if(foundErr) return EXIT_FAILURE;
    return line_counter;
}
