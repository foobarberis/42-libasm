bits 64

extern ft_strlen
extern ft_strcpy
extern malloc

global ft_strdup

section .text

; C Prototype: char *ft_strdup(const char *s1);
; -----------------------------------------------------------------------------
; Arguments:
;   - rdi: (const char *s1) The string to duplicate.
;
; Returns:
;   - rax: (char *) A pointer to the newly allocated duplicate string.
;                   NULL if allocation fails.
; -----------------------------------------------------------------------------

ft_strdup:
    push    rdi                 ; Save the original string pointer (s1) on the stack.
                                ; We need it later for ft_strcpy, but calls to ft_strlen and malloc will modify rdi.

    call    ft_strlen           ; Call ft_strlen(s1). The length will be returned in rax.

    mov     rdi, rax            ; Move the length into rdi, the first argument for malloc.
    inc     rdi                 ; Increment length by 1 to make space for the null terminator.
    call    malloc wrt ..plt    ; Call malloc(length + 1). The new memory address is in rax.

    cmp     rax, 0              ; Check if malloc failed (returned NULL).
    je      .malloc_error       ; If it failed, jump to the error handler.

    mov     rdi, rax            ; The new memory is our destination. Move its address into rdi for ft_strcpy.
    pop     rsi                 ; Restore the original string pointer from the stack into rsi, the second argument for ft_strcpy.

    call    ft_strcpy           ; Call ft_strcpy(new_memory, original_string).
                                ; ft_strcpy returns the destination pointer in rax, which is what we need to return.
    ret

.malloc_error:
    pop     rdi                 ; Clean up the stack before returning.
    mov     rax, 0              ; Malloc failure, return NULL (0).
    ret
