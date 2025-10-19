bits 64

global ft_strlen

section .text

; C Prototype: size_t ft_strlen(const char *str);
; -----------------------------------------------------------------------------
; Arguments:
;   - rdi: (const char *str) A pointer to the beginning of the string.
;
; Returns:
;   - rax: (size_t) The length of the string, excluding the null terminator.
; -----------------------------------------------------------------------------

ft_strlen:
    xor     rax, rax              ; Initialize counter (rax) to 0.

.loop:
    cmp     BYTE [rdi + rax], 0   ; Compare the character at (str + counter) with the null terminator.
    je      .end_loop             ; If the character is null ('\0'), jump to the end.
    inc     rax                   ; Otherwise, increment the counter.
    jmp     .loop                 ; Repeat the loop.

.end_loop:
    ret                           ; The final count is in rax. Return to the caller.
