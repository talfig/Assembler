#include <string.h>
#include "globals.h"

opcode get_opcode(const char *str) {
    size_t i;
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

    for(i = 0; i < OPCODE_COUNT; ++i) {
        if(!strcmp(str, opcode_map[i].name))
            return opcode_map[i].value;
    }

    return unknown_opcode; /* For unknown strings */
}

regis get_register(const char *str) {
    size_t i;
    const registerMapping register_map[] = {
            {"r0", r0}, {"r1", r1},
            {"r2", r2}, {"r3", r3},
            {"r4", r4}, {"r5", r5},
            {"r6", r6}, {"r7", r7}
    };

    for(i = 0; i < REGISTER_COUNT; ++i) {
        if(!strcmp(str, register_map[i].name))
            return register_map[i].value;
    }

    return unknown_register; /* For unknown strings */
}

instruction get_instruction(const char *str) {
    size_t i;
    const instructionMapping instruction_map[] = {
            {"data", DATA}, {"string", STRING},
            {"entry", ENTRY}, {"extern", EXTERN}
    };

    for(i = 0; i < INSTRUCTION_COUNT; ++i) {
        if(!strcmp(str, instruction_map[i].name))
            return instruction_map[i].value;
    }

    return UNKNOWN_INSTRUCTION; /* For unknown strings */
}
