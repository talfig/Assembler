/**
 * @file globals.c
 * @brief This file contains functions to map strings to their corresponding opcodes,
 * and registers in an assembler.
 */

#include <string.h>
#include "globals.h"

/**
 * @brief Retrieves the opcode corresponding to a given string.
 *
 * @param str The string representation of the opcode.
 * @return The corresponding opcode value, or `unknown_opcode` if not found.
 */
opcode get_opcode(const char *str) {
    size_t i;

    /* Array of known opcodes and their string representations */
    const opcodeMapping opcode_map[] = {
            {"mov", mov}, {"cmp", cmp},
            {"add", add}, {"sub", sub},
            {"lea", lea}, {"clr", clr},
            {"not", not}, {"inc", inc},
            {"dec", dec}, {"jmp", jmp},
            {"bne", bne}, {"red", red},
            {"prn", prn}, {"jsr", jsr},
            {"rts", rts}, {"stop", stop}
    };

    /* Iterate through the array to find the matching opcode */
    for(i = 0; i < OPCODE_COUNT; ++i) {
        if(!strcmp(str, opcode_map[i].name))
            return opcode_map[i].value;
    }

    /* Return this value if the string does not match any opcode */
    return unknown_opcode;
}

/**
 * @brief Retrieves the register corresponding to a given string.
 *
 * @param str The string representation of the register.
 * @return The corresponding register value, or `unknown_register` if not found.
 */
regis get_register(const char *str) {
    size_t i;

    /* Array of known registers and their string representations */
    const registerMapping register_map[] = {
            {"r0", r0}, {"r1", r1},
            {"r2", r2}, {"r3", r3},
            {"r4", r4}, {"r5", r5},
            {"r6", r6}, {"r7", r7}
    };

    /* Iterate through the array to find the matching register */
    for(i = 0; i < REGISTER_COUNT; ++i) {
        if(!strcmp(str, register_map[i].name))
            return register_map[i].value;
    }

    /* Return this value if the string does not match any register */
    return unknown_register;
}
