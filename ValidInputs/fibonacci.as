; file fibonacci.as

.entry MAIN
.entry FIBONACCI

.extern PRINT

macr PRINT_FIB
 prn r2
 bne END_FIB
endmacr

; Number to generate Fibonacci up to
MAIN:   mov #10, r0
        jsr FIBONACCI
        stop

FIBONACCI: mov #0, r1
; r1 = 0 (first Fibonacci number)
           mov #1, r2
; r2 = 1 (second Fibonacci number)
           prn r1
           prn r2
           jsr FIBLOOP
           rts

FIBLOOP:  cmp r0, #2
; Compare n with 2
           bne ENDLOOP
           add r1, r2
; r2 = r1 + r2
           PRINT_FIB
; Print the Fibonacci number using the macro
           mov r2, r3
; Store the last Fibonacci number in r3
           mov r2, r1
; r1 = r2 (shift r2 to r1)
           mov r3, r2
; r2 = r3 (shift r3 to r2)
           dec r0
; n = n - 1
           jmp FIBLOOP

ENDLOOP:  rts

END_FIB:  rts
