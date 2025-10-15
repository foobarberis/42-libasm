bits 64

global ft_strcpy

section .text
; char *ft_strcpy(char *dst, const char *src);
ft_strcpy:
    xor rax, rax
    jmp .loop

.loop:
    cmp BYTE [rsi + rax], 0
    je .end_loop
    mov r8b, [rsi + rax]
    mov [rdi + rax], r8b
    inc rax
    jmp .loop

.end_loop:
    mov BYTE [rdi + rax], 0
    mov rax, rdi
    ret