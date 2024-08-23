; broken_program6.as

; Instructions
0 r1, r2       ; mov r1, r2 (correct)
0 r1           ; mov r1, (missing second operand)
0 r1, r2, r3   ; mov r1, r2, r3 (extra operand)
1 r1, #5       ; cmp r1, #5 (correct)
1 r1           ; cmp r1 (missing second operand)
2 r1, #10      ; add r1, #10 (correct)
2 r1           ; add r1 (missing second operand)
2 r1, r2, r3   ; add r1, r2, r3 (extra operand)
3 r1, r2       ; sub r1, r2 (correct)
3 r1, #5       ; sub r1, #5 (correct)
3 r1           ; sub r1 (missing second operand)
4 r1, r2       ; lea r1, r2 (correct)
4 r1, #5       ; lea r1, #5 (incorrect operand type)
4 r1, r2, r3   ; lea r1, r2, r3 (extra operand)
5 r1           ; clr r1 (correct)
5             ; clr (missing operand)
6 r1           ; not r1 (correct)
6 #5           ; not #5 (incorrect operand type)
7 r1           ; inc r1 (correct)
7 r1, r2       ; inc r1, r2 (extra operand)
8 r1           ; dec r1 (correct)
8 r1, r2       ; dec r1, r2 (extra operand)
9 r1           ; jmp r1 (correct)
9 r1, r2       ; jmp r1, r2 (extra operand)
10 r1          ; bne r1 (correct)
10 r1, r2      ; bne r1, r2 (extra operand)
11 r1          ; red r1 (correct)
11 r1, r2      ; red r1, r2 (extra operand)
12 r1          ; prn r1 (correct)
12            ; prn (missing operand)
13 r1          ; jsr r1 (correct)
13 r1, r2      ; jsr r1, r2 (extra operand)
14            ; rts (correct, no operands)
14 r1         ; rts r1 (illegal operand)
15            ; stop (correct, no operands)
15 r1         ; stop r1 (illegal operand)

; Labels with Errors
GO:            ; GO: (correct)
GO: .data 1    ; GO: .data 1 (extraneous directive after label)
A:    cmp #5, r1    ; A: cmp #5, r1 (correct)
B:    cmp #5        ; B: cmp #5 (missing second operand)
C:    mov r1, r2   ; C: mov r1, r2 (correct)
D:    add r1, r2, r3 ; D: add r1, r2, r3 (extra operand)

; Macro Definitions
MACRO1 param1   ; MACRO1 param1 (correct macro definition)
MACRO1 param1, param2  ; MACRO1 param1, param2 (correct macro definition)
endmacr         ; endmacr (correct)
MACRO1 param1, param2 ; MACRO1 param1, param2 (repeated definition)
endmacr extra_text ; endmacr extra_text (extraneous text after endmacr)

; Directives with Errors
.data 10, 20, 30   ; .data 10, 20, 30 (correct)
.string "example"  ; .string "example" (correct)
.entry entry1      ; .entry entry1 (correct)
.entry entry1, entry2 ; .entry entry1, entry2 (correct)
.extern            ; .extern (correct)

; Malformed Directives
.data 1, 2, 3,    ; .data 1, 2, 3, (trailing comma)
.string "test, "missing_end_quote  ; .string "test, "missing_end_quote
.entry            ; .entry (missing argument)
.entry entry1 entry2 ; .entry entry1 entry2 (correct but contextually incorrect)
.extern extern1, extern2, ; .extern extern1, extern2, (trailing comma)

; Operand and Argument Issues
mov r1 r2        ; mov r1 r2 (missing comma)
mov r1,, r2      ; mov r1,, r2 (extra comma)
add r1 r2        ; add r1 r2 (missing comma)
lea r1,, r2      ; lea r1,, r2 (extra comma)
cmp r1 r2        ; cmp r1 r2 (missing comma)
prn,, r1         ; prn,, r1 (extra comma)

; Incorrect Operand Usage
add r1, #5       ; add r1, #5 (correct)
sub r1, r2, #10  ; sub r1, r2, #10 (extra operand)
mov r1, #label1  ; mov r1, #label1 (incorrect operand type)
lea r1, r2, #5   ; lea r1, r2, #5 (extra operand)
prn #label1      ; prn #label1 (incorrect operand type)
red r1, #5       ; red r1, #5 (incorrect operand type)

; Misformatted Labels
lbl1: some_command ; lbl1: some_command (correct)
lbl2             ; lbl2 (missing command)
lbl3: some_command, extra_text ; lbl3: some_command, extra_text (extra text)
lbl4: some_command ; lbl4: some_command (correct)
lbl5: some_command extra_text ; lbl5: some_command extra_text (extra text)