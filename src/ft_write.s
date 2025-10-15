bits 64

extern __errno_location

global ft_write

section .text
; ssize_t ft_write(int fd, const void *buf, size_t count);
ft_write:
    mov rax, 1
    syscall
    test rax, rax
    js .syscall_error
    ret

.syscall_error:
    neg rax
    mov rdi, rax
    call __errno_location wrt ..plt
    mov [rax], rdi
    mov rax, -1
    ret