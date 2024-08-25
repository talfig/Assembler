/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file macr.h
 * @brief Header file for managing macro definitions in an assembler.
 *
 * This file declares functions and structures for managing macros in an assembler.
 * It provides functions for adding, finding, freeing macros, and saving macro information from files.
 */

#ifndef MACR_H
#define MACR_H

#include "stdio.h"

/**
 * @brief Checks if a given name is a legal macro name.
 *
 * A legal macro name starts with an alphabetic character and contains only alphanumeric
 * characters or underscores. It must not exceed MAX_LABEL_SIZE.
 *
 * @param name The name to be checked.
 * @return 1 if the name is legal, 0 otherwise.
 */
int isLegalName(char *name);

/**
 * @brief Structure to represent a macro.
 *
 * This structure holds information about a macro, including its name, associated
 * information, and a pointer to the next macro in the list.
 */
typedef struct macr {
    char *name;        /**< The name of the macro */
    char *info;        /**< The information associated with the macro */
    struct macr *next; /**< Pointer to the next macro in the list */
} macr;

/**
 * @brief Structure to represent a macro table.
 *
 * This structure holds a linked list of macros, with a pointer to the head of the list.
 */
typedef struct {
    macr *head; /**< Pointer to the head of the macro list */
} macr_table;

/**
 * @brief Initializes a macro table by setting its head to NULL.
 *
 * @param tb Pointer to the macro table to be initialized.
 */
void initMacrTable(macr_table *tb);

/**
 * @brief Gets the tail macro from a macro table.
 *
 * @param tb Pointer to the macro table.
 * @return Pointer to the last macro in the table, or NULL if the table is empty.
 */
macr *getMacrTail(macr_table *tb);

/**
 * @brief Adds a macro to the macro table.
 *
 * @param tb Pointer to the macro table.
 * @param ptr Pointer to the macro to be added.
 */
void addToMacrTable(macr_table *tb, macr *ptr);

/**
 * @brief Frees all macros in the macro table and releases associated memory.
 *
 * @param tb Pointer to the macro table to be freed.
 */
void freeMacrTable(macr_table *tb);

/**
 * @brief Finds a macro by name in the macro table.
 *
 * @param tb Pointer to the macro table.
 * @param name The name of the macro to find.
 * @return Pointer to the macro if found, or NULL if not found.
 */
macr *find_macr(macr_table *tb, char *name);

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
int isLegalMacrName(macr_table *tb, char *name);

/**
 * @brief Duplicates a string by allocating memory and copying the content.
 *
 * @param s The string to be duplicated.
 * @return Pointer to the newly allocated and copied string, or NULL if memory allocation fails.
 */
char *my_strdup(const char *s);

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
int save_macr(macr_table *tb, char *name, int line_counter, FILE *fp1, FILE *fp2);

#endif /* MACR_H */
