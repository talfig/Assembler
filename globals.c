#include <string.h>
#include "globals.h"

opcode get_opcode(const char *str) {
    if (strcmp(str, "mov") == 0) return mov;
    if (strcmp(str, "cmp") == 0) return cmp;
    if (strcmp(str, "add") == 0) return add;
    if (strcmp(str, "sub") == 0) return sub;
    if (strcmp(str, "lea") == 0) return lea;
    if (strcmp(str, "clr") == 0) return clr;
    if (strcmp(str, "not") == 0) return not;
    if (strcmp(str, "inc") == 0) return inc;
    if (strcmp(str, "dec") == 0) return dec;
    if (strcmp(str, "jmp") == 0) return jmp;
    if (strcmp(str, "bne") == 0) return bne;
    if (strcmp(str, "red") == 0) return red;
    if (strcmp(str, "prn") == 0) return prn;
    if (strcmp(str, "jsr") == 0) return jsr;
    if (strcmp(str, "rts") == 0) return rts;
    if (strcmp(str, "stop") == 0) return stop;
    return opcode_none; /* For unknown strings */
}

regis get_register(const char *str) {
    if (strcmp(str, "r0") == 0) return r0;
    if (strcmp(str, "r1") == 0) return r1;
    if (strcmp(str, "r2") == 0) return r2;
    if (strcmp(str, "r3") == 0) return r3;
    if (strcmp(str, "r4") == 0) return r4;
    if (strcmp(str, "r5") == 0) return r5;
    if (strcmp(str, "r6") == 0) return r6;
    if (strcmp(str, "r7") == 0) return r7;
    return regis_none; /* For unknown strings */
}

instruct get_instruction(const char *str) {
    if (strcmp(str, "data") == 0) return DATA;
    if (strcmp(str, "string") == 0) return STRING;
    if (strcmp(str, "entry") == 0) return ENTRY;
    if (strcmp(str, "extern") == 0) return EXTERN;
    return INSTRUCT_NONE; /* For unknown strings */
}

