bits 64

extern __errno_location

global ft_write

section .text

; C Prototype: ssize_t ft_write(int fd, const void *buf, size_t count);
; -----------------------------------------------------------------------------
; Arguments:
;   - rdi: (int fd) File descriptor.
;   - rsi: (const void *buf) Pointer to the buffer to write.
;   - rdx: (size_t count) Number of bytes to write.
;
; Returns:
;   - rax: (ssize_t) On success, the number of bytes written.
;                    On error, -1, and errno is set appropriately.
; -----------------------------------------------------------------------------

ft_write:
    mov     rax, 1                     ; Syscall number for 'write' is 1.
    syscall                            ; Execute the system call.

    test    rax, rax                   ; Check if rax is negative. 'test' is like 'and' but doesn't modify the operands.
    js      .syscall_error             ; 'Jump if Sign' (negative). If rax is negative, an error occurred.
    ret                                ; Success: rax contains bytes written. Return.

.syscall_error:
    neg     rax                        ; The syscall returns a negative error code (e.g., -9 for EBADF).
                                       ; We need the positive version (9) for errno. 'neg' inverts the sign.
    push    rax                        ; Save the positive errno value.
    call    __errno_location wrt ..plt ; Get the memory address where errno is stored. rax will hold this address.
    pop     rdi                        ; Restore the positive errno value into rdi.
    mov     [rax], edi                 ; Store the errno value at the address of errno. (edi is the 32-bit part of rdi).
    mov     rax, -1                    ; Set the function's return value to -1 as per the standard.
    ret
