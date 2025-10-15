bits 64

extern __errno_location

global ft_read

section .text

; C Prototype: ssize_t ft_read(int fd, void *buf, size_t count);
; -----------------------------------------------------------------------------
; Arguments:
;   - rdi: (int fd) File descriptor.
;   - rsi: (void *buf) Pointer to the buffer to store data.
;   - rdx: (size_t count) Maximum number of bytes to read.
;
; Returns:
;   - rax: (ssize_t) On success, the number of bytes read.
;                    On error, -1, and errno is set appropriately.
; -----------------------------------------------------------------------------

ft_read:
    mov     rax, 0                     ; Syscall number for 'read' is 0.
    syscall                            ; Execute the system call.

    test    rax, rax                   ; Check if rax is negative.
    js      .syscall_error             ; If negative, an error occurred.
    ret                                ; Success: rax contains bytes read (or 0 for EOF). Return.

.syscall_error:
    neg     rax                        ; Invert the sign of the negative error code to get the positive errno value.
    push    rax                        ; Save the positive errno value.
    call    __errno_location wrt ..plt ; Get the memory address of errno into rax.
    pop     rdi                        ; Restore the positive errno value into rdi.
    mov     [rax], edi                 ; Store the errno value.
    mov     rax, -1                    ; Set the function's return value to -1.
    ret
