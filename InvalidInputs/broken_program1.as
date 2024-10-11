; file complex_broken_program1.as

.entry MAIN
.entry CALCULATE
.entry INIT

.extern PRINT

; Incorrect macro definition with multiple errors
macr BAD_MACRO, *bad
; Error: "Extraneous text after macro name"
         mov r1 r2
; Error: "Missing comma"
         add #5, invalid_dest
; Error: "Invalid destination operand"
         dec 
; Error: "Missing argument"
         rts
endmacr extra_text
; Error: "Extraneous text after \"endmacr\""

MAIN:    jsr INIT
         jsr CALCULATE
         jsr PRINT
         stop

INIT:    mov #10, r0
         mov r1, *invalid_dest
; Error: "Invalid destination operand"
         jsr BAD_MACRO
         rts

CALCULATE: 
         mov #5, r1
         add r1, ,r2
; Error: "Illegal comma"
         cmp r1, #3extra
; Error: "Unexpected operand"
         jsr PRINT_STRING
         rts

PRINT_STRING:
         prn "Hello, World
; Error: "String not properly closed with \""
         mov r1, invalid_label
; Error: "Invalid destination operand"
         rts
