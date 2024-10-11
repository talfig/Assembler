; file string_length.as

.entry MAIN
.entry STRLEN

.extern PRINT

macr INCREMENT_COUNTER
 inc r1
endmacr

MAIN:    lea msg, r0
; Load the string address into r0
         jsr STRLEN
         jsr PRINT
         stop

STRLEN:  clr r1
; r1 = 0 (initialize length counter)
STRLOOP: cmp #0, *r0
; Check if the end of the string is reached
         bne ENDSTR
         INCREMENT_COUNTER
; Increment the length counter using the macro
         inc r0
; Move to the next character
         jmp STRLOOP

ENDSTR:  rts

msg: .string "Hello, World!"
