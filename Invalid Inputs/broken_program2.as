; file complex_broken_program2.as

.entry MAIN
.entry PROCESS_DATA

.extern PRINT

; Incorrect macro name and missing name
macr 
; Error: "Missing name in macro definition"
         prn r1
endmacr

macr BAD_NAME
         prn r2
endmacr extra
; Error: "Extraneous text after macro name"

MAIN:    jsr PROCESS_DATA
         jsr PRINT
         stop

PROCESS_DATA: 
         clr r1
         mov #-100000000000, r2
; Error: "Number out of range"
         add r1, r2
         jsr INVALID_LABEL
; Error: "Undefined label"
         rts

; Invalid label, missing directive, and improper strings
bad-label:
; Error: "Invalid label"
          data 10, 20, 30
; Error: "Directive missing '.'"
          .string "Hello, World!" extraneous_text
; Error: "Extraneous text after string"
          .string "Hello, World!
; Error: "String not properly closed with \""
          .string "Hello, @World!"
; Error: "String contains invalid character"
          mov #5, ,r3
; Error: "Illegal comma"
          rts
