# Explanatory notes

When C code calls an assembly function on Linux or macOS, it follows a strict set of rules known as a "Calling Convention." This is the most critical concept to understand.

1.  **Argument Passing**: The first six integer or pointer arguments are passed in specific registers.
    *   1st Argument: `RDI`
    *   2nd Argument: `RSI`
    *   3rd Argument: `RDX`
    *   4th Argument: `RCX`
    *   5th Argument: `R8`
    *   6th Argument: `R9`

2.  **Return Value**: The function's return value **must** be placed in the `RAX` register before executing the `ret` instruction.

3.  **The Stack**: The stack is primarily used to temporarily save the state of registers before a function call (`push`) and restore them after (`pop`).

### Core Registers Reference

These are the 64-bit general-purpose registers and their roles within this project. Note that you can access their smaller parts (e.g., `EAX` for 32-bit, `AL` for the lowest 8-bit).

| Register | Role in this Project                                  |
| :------- | :---------------------------------------------------- |
| **`RAX`**    | **Return Value** from functions & **Syscall Number**. |
| **`RDI`**    | **1st Argument** (e.g., a string pointer, file descriptor). |
| **`RSI`**    | **2nd Argument** (e.g., a source string, a buffer).   |
| **`RDX`**    | **3rd Argument** (e.g., a size or count).             |
| **`RCX`**    | Used as a temporary single-byte holder (`cl`).        |
| **`R8`, `R9`** | Used for temporary storage (`r8b`, `r9b`).            |

### Memory Access Syntax

The code frequently uses the `[base + offset]` syntax to read from or write to memory.

*   **`[rdi]`**: Accesses the memory at the address stored in `rdi` (dereferencing).
*   **`[rdi + rax]`**: Accesses memory at the address calculated by adding the value in `rdi` (the base address) and the value in `rax` (the offset or index).
*   **`BYTE [...]`**: Specifies that the operation should affect only a single byte (`char`).

### CPU Flags and Conditional Jumps

Conditional jump instructions like `je` or `js` don't make decisions on their own. They rely on single-bit status registers called **flags**, which are set by preceding instructions like `cmp` or `test`.

| Flag | Name        | Set When...                        | Jumps Used in this Project                                  |
| :--- | :---------- | :--------------------------------- | :---------------------------------------------------------- |
| **ZF** | **Zero Flag** | The result of an operation is zero.  | `je` (Jump if Equal, if ZF=1), `jne` (Jump if Not Equal, if ZF=0) |
| **SF** | **Sign Flag** | The result of an operation is negative. | `js` (Jump if Sign, if SF=1)                                  |

**Example 1: The Zero Flag (ZF)**

The `cmp` instruction internally subtracts its operands. If the result is
zero (meaning the operands were equal), it sets `ZF` to 1.

```
cmp     BYTE [rdi + rax], 0   ; Is the character a null terminator?
je      .end_loop             ; Jumps to .end_loop ONLY IF ZF is 1 (the character was 0).
```

**Example 2: The Sign Flag (SF)**

The `test` instruction performs a bitwise AND. `test rax, rax` sets flags based
on the value of rax. If rax is negative, its most significant bit is 1,
which sets SF to 1.

```
test    rax, rax              ; Check the flags for the value in rax.
js      .syscall_error        ; Jumps ONLY IF SF is 1 (rax is a negative number).
```

### Instructions Used in the Project

#### Data Movement
*   `mov`: Moves data between registers or between a register and memory.
    *   *Example:* `mov r8b, BYTE [rdi + rax]` (Copy one byte from memory into the `r8b` register).
*   `push`: Pushes a register's value onto the stack. Used to save a value before it's overwritten.
*   `pop`: Pops a value from the stack into a register. Used to restore a saved value.
*   `movsx`: **Move with Sign-Extend**. Copies a smaller signed value (like a `char`) to a larger register, correctly preserving its sign (positive or negative).
    *   *Example:* `movsx rax, r8b` (Converts an 8-bit difference into a 64-bit return value for `ft_strcmp`).

#### Arithmetic & Logic
*   `inc`: Increments a register by 1. Used for loop counters.
*   `sub`: Subtracts the second operand from the first.
    *   *Example:* `sub r8b, r9b` (Calculates the difference between two characters).
*   `neg`: Negates a value (e.g., 5 becomes -5, -9 becomes 9). Used for `errno` handling.
*   `xor`: Performs a bitwise XOR. `xor rax, rax` is a fast and common idiom for setting `rax` to 0.
*   `test`: Performs a bitwise AND but only sets CPU flags. `test rax, rax` is an efficient way to check if `rax` is zero or negative.

#### Control Flow (Jumps & Calls)
*   `cmp`: Compares two operands by subtracting them internally and setting CPU flags. It does not store the result.
*   `jmp`: Unconditional jump to a label.
*   `je`: **Jump if Equal**. Jumps if the last `cmp` found the operands to be equal.
*   `jne`: **Jump if Not Equal**. Jumps if the last `cmp` found the operands to be different.
*   `js`: **Jump if Sign**. Jumps if the result of the last operation was negative. Used for syscall error checking.
*   `call`: Calls a function (pushes the return address to the stack and jumps).
*   `ret`: Returns from a function (pops the return address from the stack and jumps to it).

#### System & Assembler Directives
*   `syscall`: Triggers a kernel system call. The call number must be in `RAX`, and arguments in `RDI`, `RSI`, `RDX`, etc.
*   `global <label>`: Makes a function label visible to the linker, allowing it to be called from other files (like C).
*   `extern <label>`: Tells the assembler that a label is defined in another file (e.g., `malloc` from the C library).
*   `section .text`: A directive that declares the following lines as executable code.
