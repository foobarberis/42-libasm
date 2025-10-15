bits 64

global ft_strcmp

section .text

; C Prototype: int ft_strcmp(const char *s1, const char *s2);
; -----------------------------------------------------------------------------
; Arguments:
;   - rdi: (const char *s1) A pointer to the first string.
;   - rsi: (const char *s2) A pointer to the second string.
;
; Returns:
;   - rax: (int) The difference between the first non-matching characters.
;          < 0 if s1 < s2
;          > 0 if s1 > s2
;          = 0 if s1 == s2
; -----------------------------------------------------------------------------

ft_strcmp:
    xor     rax, rax              ; Initialize loop counter (rax) to 0.

.loop:
    mov     r8b, BYTE [rdi + rax] ; Load character from s1 into 8-bit register r8b.
    mov     r9b, BYTE [rsi + rax] ; Load character from s2 into 8-bit register r9b.
    cmp     r8b, r9b              ; Compare the two characters.
    jne     .difference           ; If they are not equal, jump to calculate the difference.
    cmp     r8b, 0                ; Check if the character from s1 was the null terminator.
    je      .difference           ; If it was, the strings are equal, so jump to return 0.
    inc     rax                   ; Move to the next character.
    jmp     .loop                 ; Repeat the loop.

.difference:
    sub     r8b, r9b              ; Calculate the difference: s1[i] - s2[i].
    movsx   rax, r8b              ; Sign-extend the 8-bit result into the 64-bit rax for the return value.
    ret                           ; This correctly handles both positive and negative results.
