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
    stop
} opcode;

typedef enum {
    r0, r1, r2, r3, r4, r5, r6, r7
} regis;

#endif /* GLOBALS_H */
