#ifndef GLOBALS_H
#define GLOBALS_H

typedef enum {
    mov,
    cmp,
    add,
    sub,
    lea,
    clr,
    not,
    inc,
    dec,
    jmp,
    bne,
    red,
    prn,
    jsr,
    rts,
    stop,
    opcode_none
} opcode;

typedef enum {
    r0, r1, r2, r3, r4, r5, r6, r7, regis_none
} regis;

typedef enum {
    DATA,
    STRING,
    ENTRY,
    EXTERN,
    INSTRUCT_NONE
} instruct;

opcode get_opcode(const char *str);

regis get_register(const char *str);

instruct get_instruction(const char *str);

#endif /* GLOBALS_H */
