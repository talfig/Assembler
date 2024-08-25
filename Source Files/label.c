/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file label.c
 * @brief This file contains functions for managing a label table in an assembler.
 *
 * It provides functionality for creating, modifying, and deleting labels within the
 * label table, as well as functions to check label properties and manage memory.
 */

#include <stdlib.h>
#include <string.h>
#include "label.h"
#include "macr.h"
#include "globals.h"
#include "errors_handling.h"

/**
 * @brief Initializes the label table by setting the head to NULL.
 *
 * @param tb Pointer to the label_table to be emptied.
 */
void initLabelTable(label_table *tb) {
    tb->head = NULL;
}

/**
 * @brief Retrieves the tail of the label table.
 *
 * @param tb Pointer to the label_table.
 * @return Pointer to the last label in the table, or NULL if the table is empty.
 */
label *getLabelTail(label_table *tb) {
    label *ptr = tb->head;

    if(!ptr) return NULL;

    /* Traverse the list to find the tail label */
    while(ptr->next) ptr = ptr->next;
    return ptr;
}

/**
 * @brief Adds a label to the end of the label table.
 *
 * @param tb Pointer to the label_table.
 * @param ptr Pointer to the label to be added.
 */
void addToLabelTable(label_table *tb, label *ptr) {
    label *tmp = getLabelTail(tb);

    /* If the table is empty, set the new label as the head */
    if(!tmp) tb->head = ptr;
    else tmp->next = ptr; /* Otherwise, add the new label at the end of the list */
}

/**
 * @brief Deletes a label from the label table.
 *
 * @param tb Pointer to the label_table.
 * @param lb Pointer to the label to be deleted.
 */
void delLabelFromTable(label_table *tb, label *lb) {
    label *ptr = tb->head;

    /* Handle case where the label to be deleted is the head of the list */
    if(ptr == lb) {
        tb->head = lb->next;
        free(lb->name);
        free(lb);
        return;
    }
    /* Traverse the list to find the label to be deleted */
    while(ptr->next != lb) ptr = ptr->next;

    ptr->next = lb->next;
    free(lb->name);
    free(lb);
}

/**
 * @brief Increases the address of data labels by a specified number.
 *
 * @param tb Pointer to the label_table.
 * @param num Number by which to increase the addresses.
 */
void increaseDataLabelTableAddress(label_table *tb, int num) {
    label *ptr = tb->head;

    /* Traverse the list and update addresses for data labels */
    while(ptr) {
        if(ptr->is_data)
            ptr->address += num;
        ptr = ptr->next;
    }
}

/**
 * @brief Frees all memory allocated for the label table.
 *
 * @param tb Pointer to the label_table to be freed.
 */
void freeLabelTable(label_table *tb) {
    label *ptr, *tmp;

    ptr = tb->head;
    while(ptr) {
        tmp = ptr;
        ptr = ptr->next;
        if(tmp->name)
            free(tmp->name);
        free(tmp);
    }
}

/**
 * @brief Finds a label by name in the label table.
 *
 * @param tb Pointer to the label_table.
 * @param name Name of the label to find.
 * @return Pointer to the label if found, or NULL if not found.
 */
label *find_label(label_table *tb, char *name) {
    label *ptr = tb->head;

    /* Traverse the list to find the label with the given name */
    while(ptr) {
        if(!strcmp(name, ptr->name))
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

/**
 * @brief Checks if a label name is legal according to various criteria.
 *
 * A legal label name is one that is a valid identifier, is not a reserved keyword or command,
 * and does not conflict with existing labels, macros, opcodes, or registers.
 *
 * @param label_tb Pointer to the label_table.
 * @param macr_tb Pointer to the macro_table.
 * @param name Name of the label to check.
 * @return 1 if the name is legal, 0 otherwise.
 */
int isLegalLabelName(label_table *label_tb, macr_table *macr_tb, char *name) {
    opcode op = get_opcode(name);
    regis rg = get_register(name);
    label *lb = find_label(label_tb, name);
    macr *mcr = find_macr(macr_tb, name);
    return  isLegalName(name) &&
            strcmp(name, "macr") != 0 &&
            strcmp(name, "endmacr") != 0 &&
            (op == unknown_opcode) &&
            (rg == unknown_register) &&
            (lb == NULL) &&
            (mcr == NULL);
}

/**
 * @brief Parses and adds a label to the label table if valid.
 *
 * This function checks if the label already exists as an entry label. If it does, it increments
 * the entry count. If the label is not legal, it returns failure. Otherwise, it allocates memory
 * for a new label, initializes its fields, and adds it to the label table.
 *
 * @param label_tb Pointer to the label_table where the label will be added.
 * @param macr_tb Pointer to the macro_table used for checking label legality.
 * @param str Name of the label to parse.
 * @param fp File pointer for error handling and cleanup.
 * @return EXIT_SUCCESS if the label was successfully parsed and added, EXIT_FAILURE otherwise.
 */
int parseLabel(label_table *label_tb, macr_table *macr_tb, char *str, FILE *fp) {
    /* Check if the label already exists and is marked as an entry */
    label *lb = find_label(label_tb, str);
    if(lb && lb->is_entry == 1) {
        lb->is_entry++;
        return EXIT_SUCCESS;
    }

    /* Validate if the label name is legal */
    if(!isLegalLabelName(label_tb, macr_tb, str)) return EXIT_FAILURE;

    lb = (label *)malloc(sizeof(label));
    if(!lb) {
        /* Handle memory allocation failure */
        fprintf(stderr, "    %s\n", getError(ALLOC_FAILED));
        freeMacrTable(macr_tb);
        freeLabelTable(label_tb);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    /* Initialize label fields */
    lb->address = 0;
    lb->is_data = 0;
    lb->is_extern = 0;
    lb->is_entry = 0;
    lb->next = NULL;

    /* Duplicate the label name */
    lb->name = my_strdup(str);
    if(!(lb->name)) {
        /* Handle failure to duplicate the label name */
        fprintf(stderr, "    %s\n", getError(ALLOC_FAILED));
        freeMacrTable(macr_tb);
        freeLabelTable(label_tb);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    /* Add the new label to the label table */
    addToLabelTable(label_tb, lb);

    return EXIT_SUCCESS;
}

/**
 * @brief Checks if there are any labels with the entry flag set.
 *
 * @param label_tb Pointer to the label_table.
 * @return 1 if there is at least one entry label, 0 otherwise.
 */
int has_entry_label(label_table *label_tb) {
    label *ptr = label_tb->head;

    /* Traverse the list to check for entry labels */
    while(ptr) {
        if(ptr->is_entry)
            return 1;
        ptr = ptr->next;
    }

    return 0;
}

/**
 * @brief Checks if there are any labels with the extern flag set.
 *
 * @param label_tb Pointer to the label_table.
 * @return 1 if there is at least one extern label, 0 otherwise.
 */
int has_extern_label(label_table *label_tb) {
    label *ptr = label_tb->head;

    /* Traverse the list to check for extern labels */
    while(ptr) {
        if(ptr->is_extern > 1)
            return 1;
        ptr = ptr->next;
    }

    return 0;
}
