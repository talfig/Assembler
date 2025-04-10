; file text_reverse.as

.entry MAIN

.extern PRINT

; Macro to compare and branch if not equal
macr m_cmp_not_eq
 cmp r1, r0
 bne NOT_END
endmacr

MAIN:   mov #0, r0
; Start index at 0
        mov #10, r1
; Length of the string
        mov #5, r2
; Position of the character to be printed (initially at the end)
        jsr REVERSE
; Jump to REVERSE to start reversing the string
        jsr PRINT
; Print the reversed string
        stop

REVERSE: mov r1, r3
; Set r3 to length of the string
        sub r0, r3
; Calculate the end position
        mov r3, r2
; Move end position to r2

NOT_END: cmp r1, r0
; Compare current index with length
        bne PRINT_CHAR
; If not end, continue

PRINT_CHAR: mov r2, r4
; Move character position to r4
        mov #0, r5
; Initialize buffer index
        add r0, r4
; Move character to buffer
        inc r0
; Move to next character
        jmp REVERSE
; Continue reversing

END:    prn r4
; Print the reversed character
        rts
