; file text_encryption.as

.entry MAIN
.entry ENCRYPT_TEXT

.extern PRINT

macr PRINT_ENCRYPTED_TEXT
 prn r1
 bne END_ENCRYPTION
endmacr

; Simple text encryption
MAIN:   mov #5, r0
        mov #0, r1
; r1 = index
        mov #5, r2
; r2 = length of text
        jsr ENCRYPT_TEXT
        stop

ENCRYPT_TEXT: mov r0, r3
; r3 = length of text
            mov r1, r4
; r4 = index
            mov r2, r5
; r5 = encryption key
            jsr LOOP_ENCRYPT
            rts

LOOP_ENCRYPT: cmp r4, r3
; Compare index with length
            bne ENCRYPT
            PRINT_ENCRYPTED_TEXT
; Print encrypted text
            rts

ENCRYPT:   add r5, r4
; Encrypt text character
           mov r4, r6
; Store encrypted character
           inc r1
; Increment index
           jmp LOOP_ENCRYPT

END_ENCRYPTION: rts
