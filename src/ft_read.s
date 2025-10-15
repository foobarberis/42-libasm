bits 64

extern __errno_location

global ft_read

section .text
; ssize_t ft_read(int fd, void *buf, size_t count);
ft_read:
    xor rax, rax
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