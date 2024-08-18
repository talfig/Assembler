/**
 * @file globals.h
 * @brief This header file defines constants, enums, and function prototypes for mapping
 * string representations of opcodes, and registers to their corresponding values.
 */

#ifndef GLOBALS_H
#define GLOBALS_H

/**
 * @def OPCODE_COUNT
 * @brief Number of opcodes supported by the assembler.
 */
#define OPCODE_COUNT 16

/**
 * @def REGISTER_COUNT
 * @brief Number of registers supported by the assembler.
 */
#define REGISTER_COUNT 8

/**
 * @enum opcode
 * @brief Enum representing the different opcodes in the assembler.
 */
typedef enum {
    mov, cmp,
    add, sub,
    lea, clr,
    not, inc,
    dec, jmp,
    bne, red,
    prn, jsr,
    rts, stop,
    unknown_opcode /**< Represents an unknown opcode */
} opcode;

/**
 * @struct opcodeMapping
 * @brief Structure for mapping a string to its corresponding opcode.
 *
 * The `opcodeMapping` structure contains a string name and the corresponding
 * opcode value, allowing the assembler to match strings to opcodes.
 */
typedef struct {
    const char *name; /**< The string representation of the opcode */
    opcode value;     /**< The corresponding opcode value */
} opcodeMapping;

/**
 * @enum regis
 * @brief Enum representing the different registers in the assembler.
 *
 * The `regis` enum includes all the supported registers and an additional value
 * `unknown_register` to handle cases where an unknown register is encountered.
 */
typedef enum {
    r0, r1, r2, r3, r4, r5, r6, r7, unknown_register /**< Represents an unknown register */
} regis;

/**
 * @struct registerMapping
 * @brief Structure for mapping a string to its corresponding register.
 */
typedef struct {
    const char *name; /**< The string representation of the register */
    regis value;      /**< The corresponding register value */
} registerMapping;

/**
 * @brief Retrieves the opcode corresponding to a given string.
 *
 * @param str The string representation of the opcode.
 * @return The corresponding opcode value, or `unknown_opcode` if not found.
 */
opcode get_opcode(const char *str);

/**
 * @brief Retrieves the register corresponding to a given string.
 *
 * @param str The string representation of the register.
 * @return The corresponding register value, or `unknown_register` if not found.
 */
regis get_register(const char *str);

#endif /* GLOBALS_H */
