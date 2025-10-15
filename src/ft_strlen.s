bits 64

global ft_strlen

section .text
; size_t ft_strlen(const char *str);
ft_strlen:
    xor rax, rax
    jmp .loop
.loop:
    cmp BYTE [rdi + rax], 0
    je .end_loop
    inc rax
    jmp .loop
.end_loop:
    ret