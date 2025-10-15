bits 64

global ft_strcpy

section .text

; C Prototype: char *ft_strcpy(char *dst, const char *src);
; -----------------------------------------------------------------------------
; Arguments:
;   - rdi: (char *dst) A pointer to the destination buffer.
;   - rsi: (const char *src) A pointer to the source string.
;
; Returns:
;   - rax: (char *) A pointer to the destination buffer (dst).
; -----------------------------------------------------------------------------

ft_strcpy:
    xor     rax, rax             ; Initialize loop counter (rax) to 0.
    mov     r8, rdi              ; Save the original destination pointer (rdi) in r8 for the return value.

.loop:
    mov     cl, BYTE [rsi + rax] ; Load one byte from src[rax] into the 8-bit register cl.
    mov     BYTE [rdi + rax], cl ; Store that byte into dst[rax].
    cmp     cl, 0                ; Check if the byte we just copied was the null terminator.
    je      .end_loop            ; If it was, we are done.
    inc     rax                  ; Increment the counter to move to the next character.
    jmp     .loop                ; Repeat the loop.

.end_loop:
    mov     rax, r8              ; Move the saved destination pointer into rax for the return.
    ret
