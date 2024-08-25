/**
 * @author Tal Figenblat
 * @date August 18, 2024
 *
 * @file label.h
 * @brief This header file defines the structures and function prototypes for managing labels in an assembler.
 *
 * It includes definitions for the `label` and `label_table` structures, as well as function prototypes
 * for operations on label tables such as adding, deleting, and finding labels. It also includes functions
 * for parsing labels and checking label properties.
 */

#ifndef LABEL_H
#define LABEL_H

#include "macr.h"
#include "globals.h"

/**
 * @struct label
 * @brief Represents a single label in the label table.
 *
 * Contains information about the label's address, name, type, and the next label in the list.
 */
typedef struct label {
    int address;        /**< Address associated with the label. */
    char *name;         /**< Name of the label. */
    int is_data;        /**< Flag indicating if the label is a data label. */
    int is_extern;      /**< Flag indicating if the label is an external label. */
    int is_entry;       /**< Flag indicating if the label is an entry label. */
    struct label *next; /**< Pointer to the next label in the list. */
} label;

/**
 * @struct label_table
 * @brief Represents a table of labels.
 *
 * Contains a pointer to the head of the label list.
 */
typedef struct {
    label *head; /**< Pointer to the first label in the table. */
} label_table;

/**
 * @brief Initializes the label table by setting the head to NULL.
 *
 * @param tb Pointer to the label_table to be emptied.
 */
void initLabelTable(label_table *tb);

/**
 * @brief Retrieves the tail of the label table.
 *
 * @param tb Pointer to the label_table.
 * @return Pointer to the last label in the table, or NULL if the table is empty.
 */
label *getLabelTail(label_table *tb);

/**
 * @brief Adds a label to the end of the label table.
 *
 * @param tb Pointer to the label_table.
 * @param ptr Pointer to the label to be added.
 */
void addToLabelTable(label_table *tb, label *ptr);

/**
 * @brief Deletes a label from the label table.
 *
 * @param tb Pointer to the label_table.
 * @param lb Pointer to the label to be deleted.
 */
void delLabelFromTable(label_table *tb, label *lb);

/**
 * @brief Increases the address of data labels by a specified number.
 *
 * @param tb Pointer to the label_table.
 * @param num Number by which to increase the addresses.
 */
void increaseDataLabelTableAddress(label_table *tb, int num);

/**
 * @brief Frees all memory allocated for the label table.
 *
 * @param tb Pointer to the label_table to be freed.
 */
void freeLabelTable(label_table *tb);

/**
 * @brief Finds a label by name in the label table.
 *
 * @param tb Pointer to the label_table.
 * @param name Name of the label to find.
 * @return Pointer to the label if found, or NULL if not found.
 */
label *find_label(label_table *tb, char *name);

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
int isLegalLabelName(label_table *label_tb, macr_table *macr_tb, char *name);

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
int parseLabel(label_table *label_tb, macr_table *macr_tb, char *str, FILE *fp);

/**
 * @brief Checks if there are any labels with the entry flag set.
 *
 * @param label_tb Pointer to the label_table.
 * @return 1 if there is at least one entry label, 0 otherwise.
 */
int has_entry_label(label_table *label_tb);

/**
 * @brief Checks if there are any labels with the extern flag set.
 *
 * @param label_tb Pointer to the label_table.
 * @return 1 if there is at least one extern label, 0 otherwise.
 */
int has_extern_label(label_table *label_tb);

#endif /* LABEL_H */
