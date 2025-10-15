bits 64

extern __errno_location
extern ft_strlen
extern ft_strcpy
extern malloc

global ft_strdup

section .text
; char *ft_strdup(const char *s1);
ft_strdup:
    push rdi
    call ft_strlen
    mov rdi, rax
    inc rdi
    call malloc wrt ..plt
    cmp rax, 0
    je .malloc_error
    mov rdi, rax
    pop rsi
    call ft_strcpy
    ret

.malloc_error:
    ret
