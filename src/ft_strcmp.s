bits 64

global ft_strcmp

section .text
; int ft_strcmp(const char *s1, const char *s2);
ft_strcmp:
    xor rax, rax
    xor r8, r8
    xor r9, r9
    jmp .loop
.loop:
    mov r8b, [rdi + rax] ; *s1
    mov r9b, [rsi + rax] ; *s2
    cmp r8b, 0
    je .end_loop
    cmp r8b, r9b
    jne .end_loop
    inc rax
    jmp .loop
.end_loop:
    sub r8, r9
    mov rax, r8
    ret