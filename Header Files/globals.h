#ifndef GLOBALS_H
#define GLOBALS_H

#define OPCODE_COUNT 16
#define REGISTER_COUNT 8
#define INSTRUCTION_COUNT 4

typedef enum {
    mov, cmp,
    add, sub,
    lea, clr,
    not, inc,
    dec, jmp,
    bne, red,
    prn, jsr,
    rts, stop,
    unknown_opcode
} opcode;

typedef struct {
    const char *name;
    opcode value;
} opcodeMapping;

typedef enum {
    r0, r1, r2, r3, r4, r5, r6, r7, unknown_register
} regis;

typedef struct {
    const char *name;
    regis value;
} registerMapping;

typedef enum {
    DATA,
    STRING,
    ENTRY,
    EXTERN,
    UNKNOWN_INSTRUCTION
} instruction;

typedef struct {
    const char *name;
    instruction value;
} instructionMapping;

opcode get_opcode(const char *str);

regis get_register(const char *str);

instruction get_instruction(const char *str);

#endif /* GLOBALS_H */
