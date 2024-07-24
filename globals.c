#include <string.h>
#include "globals.h"

opcode get_opcode(const char *str) {
    if (!strcmp(str, "mov")) return mov;
    if (!strcmp(str, "cmp")) return cmp;
    if (!strcmp(str, "add")) return add;
    if (!strcmp(str, "sub")) return sub;
    if (!strcmp(str, "lea")) return lea;
    if (!strcmp(str, "clr")) return clr;
    if (!strcmp(str, "not")) return not;
    if (!strcmp(str, "inc")) return inc;
    if (!strcmp(str, "dec")) return dec;
    if (!strcmp(str, "jmp")) return jmp;
    if (!strcmp(str, "bne")) return bne;
    if (!strcmp(str, "red")) return red;
    if (!strcmp(str, "prn")) return prn;
    if (!strcmp(str, "jsr")) return jsr;
    if (!strcmp(str, "rts")) return rts;
    if (!strcmp(str, "stop")) return stop;
    return opcode_none; /* For unknown strings */
}

regis get_register(const char *str) {
    if (!strcmp(str, "r0")) return r0;
    if (!strcmp(str, "r1")) return r1;
    if (!strcmp(str, "r2")) return r2;
    if (!strcmp(str, "r3")) return r3;
    if (!strcmp(str, "r4")) return r4;
    if (!strcmp(str, "r5")) return r5;
    if (!strcmp(str, "r6")) return r6;
    if (!strcmp(str, "r7")) return r7;
    return regis_none; /* For unknown strings */
}

instruction get_instruction(const char *str) {
    if (!strcmp(str, "data")) return DATA;
    if (!strcmp(str, "string")) return STRING;
    if (!strcmp(str, "entry")) return ENTRY;
    if (!strcmp(str, "extern")) return EXTERN;
    return INSTRUCTION_NONE; /* For unknown strings */
}

