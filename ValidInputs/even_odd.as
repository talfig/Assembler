; file even_odd.as

.entry MAIN
.entry EVENODD

.extern PRINT

macr CHECK_ODD
 sub r2, r1
 bne ODD
endmacr

MAIN:    mov #9, r0
; Number to check even or odd
         jsr EVENODD
         jsr PRINT
         stop

EVENODD: mov r0, r1
; r1 = n (number to check)
          mov #2, r2
; r2 = 2 (divider)
          CHECK_ODD
; Check if the number is odd using the macro
EVEN:    prn #1
; Print "1" for even
          rts

ODD:     prn #0
; Print "0" for odd
          rts
