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
.string "abcd"
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

## 📌 Addressing Methods (Modes)

Understanding the addressing methods used in our assembler is key to writing effective assembly code. Here’s a breakdown of the supported addressing methods:

- **(0) Immediate Addressing (#number):** In this mode, the operand is a constant value. For example, mov #5, r1 loads the value 5 directly into register r1.
- **(1) Direct Addressing (label):** This mode uses a direct reference to a memory location. For example, mov label, r2 moves the value stored at label into register r2.
- **(2) Indirect Addressing (\*register):** This method accesses memory indirectly through a register. For example, mov *r3, r4 moves the value pointed by r3 into r4.
- **(3) Indexed Addressing (register):** This method accesses the value of a base register. For instance, mov r5, r6 loads the value from the memory location of r5 into r6.

Each addressing method allows for flexible data manipulation, enabling you to write efficient and powerful assembly code.

## 👨‍💻 First Word Encoding

The assembler encodes the first word of each instruction using the following format:

| 14  | 13  | 12  | 11  | 10  |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----|----|----|
| Opcode |||| Source operand |||| Destination operand |||| The field A,R,E |||
| Fourth bit | Third bit | Second bit | First bit | Method 3 | Method 2 | Method 1 | Method 0 | Method 3 | Method 2 | Method 1 | Method 0 |  A  |  R  |  E  |

## 🧠 **Addressing Methods Encoding**

### Immediate Addressing

- **Operand Representation:** The operand itself, which is a 12-bit two's complement integer, is contained in bits 14-3 of the word.
- **A,R,E Bits:** In immediate addressing, the `A` bit is set to 1, and the other two bits (`R`, `E`) are set to 0.

### Direct Addressing

- **Operand Representation:** The operand is a memory address, with the word at this address in memory being the operand. The address is represented as a 12-bit unsigned number in bits 14-3 of the word.
- **A,R,E Bits:** 
  - If the address is internal (i.e., within the current source file), the `R` bit is set to 1, and the `A` and `E` bits are set to 0.
  - If the address is external (i.e., from another source file), the `E` bit is set to 1, and the `A` and `R` bits are set to 0.

### Indirect Register Addressing

- **Operand Representation:** Accesses memory through a pointer in a register. The content of the register is a memory address, and the word at this address is the operand. The address is represented as a 15-bit unsigned number in the register.
- **A,R,E Bits:** In indirect register addressing, the `A` bit is set to 1, and the other two bits (`R`, `E`) are set to 0.
- **Register Coding:**
  - If the operand is a destination, bits 5-3 of the word contain the register number used as a pointer.
  - If the operand is a source, bits 8-6 of the word contain the register number used as a pointer.
  - If there are two operands using indirect register addressing, both registers share the same word, with bits 5-3 containing the destination register and bits 8-6 containing the source register.

### Direct Register Addressing

- **Operand Representation:** The operand is a direct register.
- **A,R,E Bits:** In direct register addressing, the `A` bit is set to 1, and the other two bits (`R`, `E`) are set to 0.
- **Register Coding:**
  - If the register is a destination, bits 5-3 of the word contain the register number.
  - If the register is a source, bits 8-6 of the word contain the register number.
  - If there are two operands using either direct register or indirect register addressing, both registers share the same word, with bits 5-3 containing the destination register and bits 8-6 containing the source register.

### Unused Bits

- Any bits in the instruction word that are not used should be set to 0.

## 📚 **Types of Statements in Assembly Language**

Assembly language typically includes four types of statements:

| **Statement Type**    | **Explanation**                                                                                                  |
|-----------------------|------------------------------------------------------------------------------------------------------------------|
| **Empty Statement**    | A line that contains only whitespace (spaces, tabs, etc.). Essentially, it does nothing and will be ignored during compilation. |
| **Comment Statement**  | A line beginning with a semicolon `;` which is used to comment out code or add explanations in the assembly source. These are also ignored by the assembler. |
| **Instruction Statement** | A line containing valid assembly code that the assembler will translate into machine language. These lines typically contain an opcode and operands. |
| **Directive Statement**  | A line that starts with a dot `.` followed by a directive keyword (e.g., `.entry`, `.extern`). These lines instruct the assembler on how to process the subsequent code. |

### 🧰 **Instruction Statements**

**1. `.data` Instruction**
- The `.data` instruction allocates space in the data image to store the specified integer values.
- Parameters: One or more legal integers separated by commas.

Example:

  ```assembly
  .data 7, -57, +17, 9
  ```

In this example, the assembler allocates four consecutive words in the data image for the numbers. If a label is defined, it will be associated with the address of the first value.

```assembly
XYZ: .data 7, -57, +17, 9
```

Here, XYZ is a label associated with the address of the first value (7). This label can be referenced in the program.

**2. `.string` Instruction**
- The `.string` instruction allocates space in the data image to store a string.
- Parameters: A single legal string enclosed in double quotes.

Example:

```assembly
STR: .string "abcdef"
```
The string "abcdef" is stored in the data image with each character in a separate word, followed by a `0` to indicate the end of the string. The label `STR` refers to the address of the first character.

**3. `.entry` Instruction**
- The `.entry` instruction identifies a label that can be referenced from other assembly source files.
- Parameters: A single label name defined in the current source file.

Example:

```assembly
.entry HELLO
```

This instruction marks the label HELLO as available for external reference.

**4. `.extern` Instruction**
- The `.extern` instruction indicates that a label is defined in another source file.
- Parameters: A single label name that is defined externally.

Example:

```assembly
.extern HELLO
```

This indicates that the label HELLO is defined in another source file and will be linked accordingly.

### 🛑 Instruction Fields

**1. Labels**
- A label is a symbolic representation of an address in memory.
- Syntax:
  -  Maximum length: 31 characters.
  -  Ends with a colon `:`, which must be directly attached to the label name without spaces.

Example:

```assembly
Hello:
X:
He10:
```

Labels are case-sensitive and must be unique within the same file.

**2. Numbers**
- Legal numbers are decimal integers that can be positive or negative.

Example:

```assembly
123, -57, +17
```

**3. Strings**
- A legal string is a sequence of printable ASCII characters enclosed in double quotes.

Example:

```assembly
"hello world"
```

### 📋 Instruction Statement Formats

**1. Two-Operand Instruction**
- Format: `label: opcode source-operand, target-operand`

Example:

```assembly
HELLO: add r7, B
```

**2. One-Operand Instruction**
- Format: `label: opcode target-operand`

Example:

```assembly
HELLO: bne XYZ
```

**3. No-Operand Instruction**
- Format: `label: opcode`

Example:

```assembly
END: stop
```

## 🔍 Macro Handling

When the assembler receives an assembly program, it first expands all macros before proceeding with the assembly process. If there are macros, the assembler generates an expanded program, which is then assembled into machine code. Here's how a sample program looks before and after macro expansion:

Before Macro Expansion:

```assembly
MAIN: add r3, LIST
LOOP: prn #48
macr m_macr
cmp r3, #-6
bne END
endmacr
lea STR, r6
inc r6
mov *r6, K
sub rl, r4
m_macr
dec K
jmp LOOP
END: stop
STR: .string "abcd"
LIST: .data 6, -9
K: .data 31
```

After Macro Expansion:

```assembly
MAIN: add r3, LIST
LOOP: prn #48
lea STR, r6
inc r6
mov *r6, K
sub rl, r4
cmp r3, #-6
bne END
dec K
jmp LOOP
END: stop
STR: .string "abcd"
LIST: .data 6, -9
K: .data 31
```

## ⚙️ **Supported Operations and Addressing Methods**

Our assembler supports the following operations and the corresponding addressing methods:

| **Operation** | **Source Operand Addressing Methods** | **Destination Operand Addressing Methods** |
|---------------|-------------------------------------|------------------------------------------|
| `mov`         | 0,1,2,3                             | 1,2,3                                    |
| `cmp`         | 0,1,2,3                             | 0,1,2,3                                  |
| `add`         | 0,1,2,3                             | 1,2,3                                    |
| `sub`         | 0,1,2,3                             | 1,2,3                                    |
| `lea`         | 1                                   | 1,2,3                                    |
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

Additionally, the assembler should replace the symbols `K`, `STR`, `LIST`, `MAIN`, `LOOP`, `END` with the memory addresses where each corresponding data or instruction is located.

### 📈 First Pass

In the first pass, rules are required to determine the address to be assigned to each symbol. The basic principle is to count the memory locations occupied by the instructions. If each instruction is loaded into memory at the location following the previous instruction, such counting will indicate the address of the next instruction. This counting is performed by the assembler and is maintained in the instruction counter (IC). The initial value of IC is 100 (decimal), so the machine code of the first instruction is constructed to load into memory starting from address 100. The IC is updated with each instruction line that allocates space in memory. After the assembler determines the length of the instruction, the IC is increased by the number of cells (words) occupied by the instruction, and thus it points to the next available cell.

As mentioned, to encode instructions in machine language, the assembler maintains a table that contains a corresponding code for each operation name. During translation, the assembler replaces each operation name with its code, and each operand is replaced with its corresponding encoding. However, this replacement process is not so simple. The instructions use various addressing methods for operands. The same operation can have different meanings in each addressing method, and therefore different encodings are applied depending on the addressing methods. For example, the `mov` operation can refer to copying the content of a memory cell to a register or copying the content of one register to another, and so on. Each such possibility of `mov` might have a different encoding.

The assembler needs to scan the entire instruction line and decide on the encoding based on the operands. Typically, the encoding is divided into a field for the operation name and additional fields containing information about the addressing methods. All fields together require one or more words in the machine code.

When the assembler encounters a label at the beginning of the line, it recognizes it as a label definition and assigns it an address - the current content of the IC. Thus, all labels receive their addresses at the time of definition. These labels are entered into the symbol table, which, in addition to the label name, contains the address and additional attributes. When a label is referred to in the operand of any instruction, the assembler can retrieve the corresponding address from the symbol table.

An instruction can also refer to a symbol that has not yet been defined in the program but will be defined later. For example, consider a branch instruction to an address defined by the label `A` that appears later in the code:

```assembly
bne A
...
A:
```

### 📊 Second Pass

As seen in the first pass, the assembler cannot construct the machine code of operands using symbols that have not yet been defined. Only after the assembler has scanned the entire program, so that all symbols have already been entered into the symbol table, can the assembler complete the machine code of all operands.

To achieve this, the assembler performs a second pass over the source code. During this pass, it updates the machine code for operands by substituting the symbols with their corresponding values from the symbol table. By the end of this second pass, the entire program is fully translated into machine code.

## 📜 Example Program

Here’s a quick demo of an assembly program in action:

Pre-assembler program:

```assembly
; file ps.as 
.entry LIST 
.extern fn1 
MAIN: add r3, LIST 
jsr fn1 
LOOP: prn #48 
 lea STR, r6 
 inc r6 
 mov *r6, L3 
 sub r1, r4 
 cmp r3, #-6 
 bne END 
 add r7, *r6 
 clr K 
 sub L3, L3 
.entry MAIN 
 jmp LOOP 
END: stop 
STR: .string "abcd" 
LIST: .data 6, -9 
 .data -100 
K: .data 31 
.extern L3
```

Post-assembler program:

```bash
  32 9
0100 12024
0101 00304
0102 02112
0103 64024
0104 00001
0105 60014
0106 00604
0107 20504
0108 02042
0109 00064
0110 34104
0111 00064
0112 01024
0113 00604
0114 00001
0115 16104
0116 00144
0117 06014
0118 00304
0119 77724
0120 50024
0121 02032
0122 12044
0123 00764
0124 24024
0125 02142
0126 14424
0127 00001
0128 00001
0129 44024
0130 01512
0131 74004
0132 00141
0133 00142
0134 00143
0135 00144
0136 00000
0137 00006
0138 77767
0139 77634
0140 00037
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
