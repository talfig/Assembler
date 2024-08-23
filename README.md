<h1 align="center">🔧 Assembler: The Code Converter</h1>

<p align="center">
  Welcome to the ultimate assembler built in C! Transform your assembly code into machine language with flair and precision.
  <br>
  🛠️ Custom Assembly Language | 🌟 Macro Magic | 💡 Detailed Error Reporting
</p>

## 🚀 Features

- **Custom Assembly Language:** Dive into our unique assembly language with a defined set of opcodes.
- **Macro Wizardry:** Create and use powerful macros to streamline your assembly code.
- **Smart Error Handling:** Get detailed, compiler-like error messages to troubleshoot with ease.

## 🧩 Supported Opcodes

Our assembler brings to life a variety of opcodes for your coding pleasure:

- (0) `mov` – Move data
- (1) `cmp` – Compare values
- (2) `add` – Addition
- (3) `sub` – Subtraction
- (4) `lea` – Load effective address
- (5) `clr` – Clear data
- (6) `not` – Bitwise NOT
- (7) `inc` – Increment
- (8) `dec` – Decrement
- (9) `jmp` – Jump to address
- (10) `bne` – Branch if not equal
- (11) `red` – Read input
- (12) `prn` – Print output
- (13) `jsr` – Jump to subroutine
- (14) `rts` – Return from subroutine
- (15) `stop` – Halt execution

## ✍️ Assembly Language Syntax

Write your assembly code with these cool features:

- **Macros:** Define macros with macr <macro_name>, include a series of instructions, and close with endmacr. This helps to simplify repetitive code.

Example:

```assembly
macr myMacro
    mov r1, r2
    add r3, r4
endmacr
```

- **Directives:** Use special commands like .entry, .extern, and more to manage your code's structure.

Example:

```assembly
.extern var1
.entry start
```


- **Instructions:** Use our supported opcodes to perform operations in your assembly code. Each opcode corresponds to a specific machine instruction.

Example:

```assembly
mov r1, r2
add r3, r4
jmp start
```

- **Labels:** Define and use labels in your code.

Example:

```assembly
label: mov r1, r2
```

Each instruction and operation is carefully designed to give you complete control over your assembly code, allowing you to write efficient and functional programs.

## 📌 Addressing Methods (Modes)
Understanding the addressing methods used in our assembler is key to writing effective assembly code. Here’s a breakdown of the supported addressing methods:

- **(0) Immediate Addressing (#):** In this mode, the operand is a constant value. For example, mov #5, r1 loads the value 5 directly into register r1.
- **(1) Direct Addressing: (label)** This mode uses a direct reference to a memory location. For example, mov label, r2 moves the value stored at label into register r2.
- **(2) Indirect Addressing (\*register):** This method accesses memory indirectly through a register. For example, mov *r3, r4 moves the value pointed by r3 into r4.
- **(3) Indexed Addressing (register):** This method accesses the value of a base register. For instance, mov r5, r6 loads the value from the memory location of r5 into r6.

Each addressing mode allows for flexible data manipulation, enabling you to write efficient and powerful assembly code.

## 📊 First Word Encoding

The assembler encodes the first word of each instruction using the following format:

| 14  | 13  | 12  | 11  | 10  |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----|----|----|
| Opcode |||| Source operand |||| Destination operand |||| The field A, R, E |||
||||| Mode 3 | Mode 2 | Mode 1 | Mode 0 | Mode 3 | Mode 2 | Mode 1 | Mode 0 |  A  |  R  |  E  |

### 📚 **Types of Statements in Assembly Language**

Assembly language typically includes four types of statements:

| **Statement Type**    | **Explanation**                                                                                                  |
|-----------------------|------------------------------------------------------------------------------------------------------------------|
| **Empty Statement**    | A line that contains only whitespace (spaces, tabs, etc.). Essentially, it does nothing and will be ignored during compilation. |
| **Comment Statement**  | A line beginning with a semicolon `;` which is used to comment out code or add explanations in the assembly source. These are also ignored by the assembler. |
| **Instruction Statement** | A line containing valid assembly code that the assembler will translate into machine language. These lines typically contain an opcode and operands. |
| **Directive Statement**  | A line that starts with a dot `.` followed by a directive keyword (e.g., `.entry`, `.extern`). These lines instruct the assembler on how to process the subsequent code. |

### ⚙️ **Supported Operations and Addressing Modes**

Our assembler supports the following operations and the corresponding addressing modes:

| **Operation** | **Source Operand Addressing Modes** | **Destination Operand Addressing Modes** |
|---------------|-------------------------------------|------------------------------------------|
| `mov`         | 0,1,2,3                             | 0,1,2,3                                  |
| `cmp`         | 0,1,2,3                             | 0,1,2,3                                  |
| `add`         | 0,1,2,3                             | 1,2,3                                    |
| `sub`         | 0,1,2,3                             | 1,2,3                                    |
| `lea`         | 1                                   | 0,1,2,3                                  |
| `clr`         | -                                   | 1,2,3                                    |
| `not`         | -                                   | 1,2,3                                    |
| `inc`         | -                                   | 1,2,3                                    |
| `dec`         | -                                   | 1,2,3                                    |
| `jmp`         | -                                   | 1,2                                      |
| `bne`         | -                                   | 1,2                                      |
| `red`         | -                                   | 1,2,3                                    |
| `prn`         | -                                   | 0,1,2,3                                  |
| `jsr`         | -                                   | 1,2                                      |
| `rts`         | -                                   | -                                        |
| `stop`        | -                                   | -                                        |

## 🔁 Assembler with Two Passes

In the first pass of the assembler, the program reads the assembly code to determine the symbols (labels) appearing in the program, assigns an address to each symbol, and builds the symbol table. In the second pass, using the symbol table, the assembler generates the actual machine code.

Our assembler handles the following instructions during the second pass: `mov`, `jmp`, `prn`, `sub`, `cmp`, `inc`, `bne`, `stop`. The corresponding machine code is generated based on the opcode and the operands provided.

You can replace the names of the operation functions such as `K`, `STR`, `LIST`, `MAIN`, `LOOP`, `END` in the assembler with names that match each function's purpose.

### 📜 Example Program

Here’s a quick demo of an assembly program in action:

```assembly
; Assembly Program
start:  mov r1, r2
        add r3, r4
        stop
```

## 🛠️ Installation
Ready to build? Follow these steps:

**1.** Ensure you have a C compiler installed.

**2.** Clone this repository with:

```bash
git clone https://github.com/talfig/Assembler.git
```

**3.** Navigate to the project directory and run:

```bash
make
```

You’ll have the assembler ready in no time!

## 🎯 Usage
To run the assembler on a certain file:

```bash
./assembler <source_file>
```

Replace <source_file> with the path to your assembly code file.

## ⚠️ Error Handling
Bumped into issues? No worries! Our assembler offers descriptive error messages such as:

- **Memory allocation failure**
- **Unrecognized commands**
- **Syntax errors**

## 📁 Directory Structure
The project is organized as follows:

- **Build and Configuration:** Contains build scripts and configuration files.
- **Header Files:** Contains header files for the project.
- **Invalid Inputs:** Contains input files that are expected to cause errors.
- **Invalid Outputs:** Contains output files corresponding to invalid inputs.
- **Source Files:** Contains the source code files.
- **Valid Inputs:** Contains input files that should be processed correctly.
- **Valid Outputs:** Contains output files corresponding to valid inputs.
- **Object Files:** Contains object files generated during compilation.
