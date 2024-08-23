<h1 align="center">🔧 Assembler: The Code Converter</h1>

<p align="center">
  Welcome to the ultimate assembler built in C! Transform your assembly code into machine language with flair and precision.
  <br>
  🎨 Custom Assembly Language | 🌟 Macro Magic | 💡 Detailed Error Reporting
</p>

## 📝 Project Background and Objectives

As is known, there are many programming languages, and a large number of programs written in different languages can run on the same computer. How does the computer recognize so many languages? The answer is simple: the computer actually understands only one language: machine code, which is stored in memory as a sequence of binary digits. This code is divided by the Central Processing Unit (CPU) into small segments with meaning: instructions, addresses, and data.

In fact, computer memory is an array of bits, usually grouped into fixed-size units (bytes, words). There is no physical difference, visible to an unskilled eye, between the part of memory where a program is located and the rest of the memory.

The CPU can perform a variety of simple operations called machine instructions, using the registers within the CPU and the computer memory. Examples include transferring a number from memory to a register or back, adding 1 to a number in a register, checking if a number in a register is zero, and performing addition and subtraction between two registers.

Machine instructions and their combinations make up the program as it is loaded into memory. Each source program (the program as written by the programmer) will eventually be translated into this final form by a special software tool.

The CPU executes code in the format of machine language. This is a sequence of bits representing a binary encoding of a series of machine instructions making up the program. This code is not readable to users and thus it is not convenient to write or read programs directly in machine language. Assembly language allows representing machine instructions in a more symbolic and user-friendly manner. However, it still needs to be translated into machine code for the program to run on the computer. This translation is done by a tool called an assembler.

Each CPU model (i.e., each computer architecture) has its own specific machine language and, correspondingly, its own specific assembly language. Therefore, each assembler (translation tool) is dedicated and unique to each CPU.

The task of the assembler is to create a file containing machine code from a given source file written in assembly language. This is the first step in the process of getting a program ready to run on computer hardware. The subsequent steps are linking and loading, but these are not covered in this context.

The goal of this project is to write an assembler (i.e., a program that translates into machine code) for a specifically defined assembly language for this project.


## 🖥️ **Hardware**

- The computer in this project is comprised of a CPU (Central Processing Unit) - a work unit containing registers and RAM. Some of the memory also serves as a stack.

- The CPU contains 8 general registers: `r0, r1, r2, r3, r4, r5, r6, r7`. The size of each register is 15 bits. The content of the registers is initialized to 0, and the least significant 3 bits of each register are always written as the letter 'z' in lowercase.

- Additionally, the CPU contains a register named PSW (program status word), which contains several flags representing the status of the program at any given moment. These flags are typically used to indicate conditions like carry or overflow after arithmetic operations.

- The memory size is 4096 bytes, addressed from 0-4095, with each address being 15 bits long. The memory content is treated as "words", similar to registers.

- The machine works with a big-endian system, meaning the most significant byte is stored at the smallest memory address. The numbers are stored using 2's complement (negative numbers), and characters are encoded in ASCII.

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
.extern start
.entry end
.string "str"
.data 1, -5, 0
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

## 📌 Addressing Methods
Understanding the addressing methods used in our assembler is key to writing effective assembly code. Here’s a breakdown of the supported addressing methods:

- **(0) Immediate Addressing (#):** In this mode, the operand is a constant value. For example, mov #5, r1 loads the value 5 directly into register r1.
- **(1) Direct Addressing: (label)** This mode uses a direct reference to a memory location. For example, mov label, r2 moves the value stored at label into register r2.
- **(2) Indirect Addressing (\*register):** This method accesses memory indirectly through a register. For example, mov *r3, r4 moves the value pointed by r3 into r4.
- **(3) Indexed Addressing (register):** This method accesses the value of a base register. For instance, mov r5, r6 loads the value from the memory location of r5 into r6.

Each addressing mode allows for flexible data manipulation, enabling you to write efficient and powerful assembly code.

## 👨‍💻 First Word Encoding

The assembler encodes the first word of each instruction using the following format:

| 14  | 13  | 12  | 11  | 10  |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----|----|----|
| Opcode |||| Source operand |||| Destination operand |||| The field A,R,E |||
| Fourth bit | Third bit | Second bit | First bit | Method 3 | Method 2 | Method 1 | Method 0 | Method 3 | Method 2 | Method 1 | Method 0 |  A  |  R  |  E  |

## 📊 Extra Word Encoding for Addressing Methods

In an assembler, the extra word refers to additional data that is required when using certain addressing methods. This data is encoded during the assembly process and is essential for executing the instruction correctly. Here's how the extra word is handled for each addressing method and the overall encoding process:

### Immediate Addressing (Method 0)
- **Description:** The operand is a constant value provided directly in the instruction.
- **Extra Word:** Required. The extra word contains the actual immediate value that is to be used in the operation.
- **Encoding Process:** 
  - The opcode is encoded in the first word, followed by the mode bits indicating immediate addressing.
  - The immediate value is placed in the extra word.
  - Example: 
    ```assembly
    mov #5, r1
    ```
    Here, the immediate value `5` is stored as the extra word.

### Direct Addressing (Method 1)
- **Description:** The operand is a memory address directly specified in the instruction.
- **Extra Word:** Required. The extra word contains the address of the operand in memory.
- **Encoding Process:** 
  - The opcode is encoded in the first word, followed by the mode bits indicating direct addressing.
  - The memory address is placed in the extra word.
  - Example:
    ```assembly
    mov label, r2
    ```
    The address corresponding to `label` is stored in the extra word.

### Indirect Addressing (Method 2)
- **Description:** The operand is a memory address stored in a register, and the instruction operates on the value at that address.
- **Extra Word:** Required. The extra word contains the register that holds the memory address.
- **Encoding Process:** 
  - The opcode is encoded in the first word, followed by the mode bits indicating indirect addressing.
  - The extra word contains the value stored in the register pointing to the memory location.
  - Example:
    ```assembly
    mov *r3, r4
    ```
    The address stored in `r3` is used, and its value is moved to `r4`.

### Indexed Addressing (Method 3)
- **Description:** The operand is accessed using a base register plus an offset.
- **Extra Word:** Required. The extra word contains the base register and the offset value.
- **Encoding Process:** 
  - The opcode is encoded in the first word, followed by the mode bits indicating indexed addressing.
  - The extra word contains the base register value and the offset.
  - Example:
    ```assembly
    mov r5, r6
    ```
    The content at `r5` (considering offset if any) is loaded into `r6`.

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

## 🌐 License
This project is licensed under the MIT License - see the LICENSE file for details.
