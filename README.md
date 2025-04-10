<!-- Assembler Headline -->
<h1 align="center">🔧 Assembler: The Code Converter</h1>

<!-- Welcome Description -->
<p align="center">
  Welcome to the ultimate assembler built in C, designed to transform your assembly code into machine language with precision and elegance.
  <br>
  🎨 Custom Assembly Language | 🌟 Macro Magic | 💡 Detailed Error Reporting
</p>

<p align="center">
  <!-- GitHub Stars -->
  <a href="https://github.com/talfig/Assembler">
    <img src="https://img.shields.io/github/stars/talfig/Assembler?color=ff69b4&label=Stars&logo=github&style=flat-square" alt="GitHub stars">
  </a>
  <!-- GitHub Forks -->
  <a href="https://github.com/talfig/Assembler/fork">
    <img src="https://img.shields.io/github/forks/talfig/Assembler?color=ffd700&label=Forks&logo=github&style=flat-square" alt="GitHub forks">
  </a>
  <!-- Repo Views -->
  <a href="https://github.com/talfig/Assembler">
    <img src="https://komarev.com/ghpvc/?username=talfig-Assembler&label=Repo%20views&color=ff6347&style=flat-square" alt="Repo views">
  </a>
  <!-- License -->
  <a href="https://github.com/talfig/Assembler/blob/main/LICENSE">
    <img src="https://img.shields.io/badge/license-AGPL-blue.svg" alt="License">
  </a>
</p>

<p align="center">
  <!-- Contributions Welcome -->
  <a href="https://github.com/talfig/Assembler">
    <img src="https://img.shields.io/badge/Contributions-Welcome-00c4cc?style=flat-square" alt="Contributions Welcome">
  </a>
  <!-- Made with Love -->
  <a href="https://github.com/talfig/Assembler">
    <img src="https://img.shields.io/badge/Made%20with%20♥-00c4cc?style=flat-square" alt="Made with Love">
  </a>
</p>

<!-- Creator -->
<h2 align="center">🌌 Creator: Tal Figenblat 🌌</h2>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#project-background-and-objectives">Project Background and Objectives</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#hardware">Hardware</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#features">Features</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#supported-opcodes">Supported Opcodes</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#opcodes-specification">Opcodes Specification</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#first-group-two-operand-opcodes">First Group: Two-Operand Opcodes</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#second-group-one-operand-opcodes">Second Group: One-Operand Opcodes</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#third-group-no-operand-opcodes">Third Group: No-Operand Opcodes</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#assembly-language-syntax">Assembly Language Syntax</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#macros">Macros</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#directives">Directives</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#instructions">Instructions</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#variables-labels">Variables (Labels)</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#addressing-methods-modes">Addressing Methods (Modes)</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#addressing-methods-for-operations">Addressing Methods for Operations</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#first-word-encoding">First Word Encoding</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#opcodes">Opcodes (Bits 14-11)</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#source-operand">Source Operand (Bits 10-7)</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#destination-operand">Destination Operand (Bits 6-3)</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#a-r-e-field">A,R,E Field (Bits 2-0)</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#addressing-methods-encoding">Addressing Methods Encoding</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#immediate-addressing">Immediate Addressing</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#direct-addressing">Direct Addressing</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#indirect-register-addressing">Indirect Register Addressing</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#direct-register-addressing">Direct Register Addressing</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#unused-bits">Unused Bits</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#types-of-statements-in-assembly-language">Types of Statements in Assembly Language</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#directive-statements">Directive Statements</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#data-directive">".data" Directive</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#string-directive">".string" Directive</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#entry-directive">".entry" Directive</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#extern-directive">".extern" Directive</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#instruction-fields">Instruction Fields</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#labels">Labels</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#numbers">Numbers</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#strings">Strings</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#instruction-statement-formats">Instruction Statement Formats</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#two-operand-instruction">Two-Operand Instruction</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#one-operand-instruction">One-Operand Instruction</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#no-operand-instruction">No-Operand Instruction</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#the-a-r-e-field-encoding">The A,R,E Field Encoding</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#the-a-r-e-bits">The A,R,E Bits</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#macro-handling">Macro Handling</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#assembler-with-two-passes">Assembler with Two Passes</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#first-pass">First Pass</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#second-pass">Second Pass</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#object-file-format">Object File Format</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#entries-file-format">Entries File Format</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#externals-file-format">Externals File Format</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#example-program">Example Program</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#installation">Installation</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#linux">Linux</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#github-codespaces">GitHub Codespaces</a></li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#usage">Usage</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#error-handling">Error Handling</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#directory-structure">Directory Structure</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#appendix">Appendix</a>
      <ul>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#program-status-word-psw">Program Status Word (PSW)</a></li>
        <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#linking-and-loading">Linking and Loading</a>
          <ul>
            <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#linking">Linking</a></li>
            <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#loading">Loading</a></li>
          </ul>
        </li>
      </ul>
    </li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#license">License</a></li>
    <li><a href="https://github.com/talfig/Assembler/blob/main/README.md#contact">Contact</a></li>
  </ol>
</details>

<!-- Project Background and Objectives -->
<h2 id="project-background-and-objectives">📝 Project Background and Objectives</h2>

As is known, there are many programming languages, and a large number of programs written in different languages can run on the same computer. How does the computer recognize so many languages? The answer is simple: the computer actually understands only one language: machine code, which is stored in memory as a sequence of binary digits. This code is divided by the Central Processing Unit (CPU) into small segments with meaning: instructions, addresses, and data.

In fact, computer memory is an array of bits, usually grouped into fixed-size units (bytes, words). There is no physical difference, visible to an unskilled eye, between the part of memory where a program is located and the rest of the memory.

The CPU can perform a variety of simple operations called machine instructions, using the registers within the CPU and the computer memory. Examples include transferring a number from memory to a register or back, adding 1 to a number in a register, checking if a number in a register is zero, and performing addition and subtraction between two registers.

Machine instructions and their combinations make up the program as it is loaded into memory. Each source program (the program as written by the programmer) will eventually be translated into this final form by a special software tool.

The CPU executes code in the format of machine language. This is a sequence of bits representing a binary encoding of a series of machine instructions making up the program. This code is not readable to users and thus it is not convenient to write or read programs directly in machine language. Assembly language allows representing machine instructions in a more symbolic and user-friendly manner. However, it still needs to be translated into machine code for the program to run on the computer. This translation is done by a tool called an assembler.

Each CPU model (i.e., each computer architecture) has its own specific machine language and, correspondingly, its own specific assembly language. Therefore, each assembler (translation tool) is dedicated and unique to each CPU.

The task of the assembler is to create a file containing machine code from a given source file written in assembly language. This is the first step in the process of getting a program ready to run on computer hardware. The subsequent steps are linking and loading, but these are not covered in this context.

The goal of this project is to write an assembler (i.e., a program that translates into machine code) for a specifically defined assembly language for this project.

<details>
  <summary>Executable Code Process</summary>
  <p align="center">
    <a href="https://github.com/talfig/Assembler">
      <img src="https://github.com/talfig/Assembler/blob/main/exe_code_process.svg" alt="Executable Code Process">
    </a>
  </p>
</details>

<!-- Hardware -->
<h2 id="hardware">🖥️ Hardware</h2>

- The computer in this project is comprised of a CPU (Central Processing Unit) - a work unit containing registers and RAM. Some of the memory also serves as a stack.

- The CPU contains 8 general registers: `r0, r1, r2, r3, r4, r5, r6, r7`. Each register is 15 bits in size, with the least significant bit labeled as bit 0 and the most significant bit as bit 14. The content of the registers is initialized to 0. Register names are always written with a lowercase 'r'.

- Additionally, the CPU contains a register named PSW (program status word), which contains several flags representing the status of the program at any given moment. These flags are typically used to indicate conditions like carry or overflow after arithmetic operations. For more details on the PSW, please refer to the [Program Status Word (PSW)](https://github.com/talfig/Assembler/blob/main/README.md#program-status-word-psw) section in the appendix.

- The memory size is 4096 bytes, addressed from 0-4095, with each address being 15 bits long. The memory content is treated as "words", similar to registers.

- The machine works with a big-endian system, meaning the most significant byte is stored at the smallest memory address. The numbers are stored using 2's complement (negative numbers), and characters are encoded in ASCII.

<!-- Features -->
<h2 id="features">🚀 Features</h2>

- **Custom Assembly Language:** Dive into our unique assembly language with a defined set of opcodes.
- **Macro Efficiency:** Create and use powerful macros to streamline your assembly code.
- **Smart Error Handling:** Get detailed, compiler-like error messages to troubleshoot with ease.

<!-- Supported Opcodes -->
<h2 id="supported-opcodes">🕹️ Supported Opcodes</h2>

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

<!-- Opcodes Specification -->
<h2 id="opcodes-specification">🧩 Opcodes Specification</h2>

The CPU in this project includes a `Program Counter` (PC), an internal register (not a general-purpose register) that contains the memory address of the current instruction being executed. Instructions are divided into three groups based on the number of operands they require.

<!-- First Group: Two-Operand Opcodes -->
<h3 id="first-group-two-operand-opcodes">☝️ First Group: Two-Operand Opcodes</h3>

These instructions use two operands:

- **mov**: Copies the content of the source operand to the destination operand.
  - Example: `mov A, r1` – Copies the value from memory address `A` to register `r1`.
- **cmp**: Compares the value of the source operand with the destination operand. The comparison results affect the flags in the PSW.
  - Example: `cmp A, r1` – Compares the value at memory address `A` with the value in register `r1`. The Z flag in the PSW is set if they are equal.
- **add**: Adds the value of the source operand to the destination operand and stores the result in the destination.
  - Example: `add A, r0` – Adds the value from memory address `A` to register `r0` and stores the result in `r0`.
- **sub**: Subtracts the value of the source operand from the destination operand and stores the result in the destination.
  - Example: `sub #2, r1` – Subtracts `2` from the value in register `r1` and stores the result in `r1`.
- **lea**: Loads the effective address of the source operand into the destination register.
  - Example: `lea HELLO, r1` – Loads the address of `HELLO` into register `r1`.

<!-- Second Group: One-Operand Opcodes -->
<h3 id="second-group-one-operand-opcodes">✌️ Second Group: One-Operand Opcodes</h3>

These instructions require only one operand:

- **clr**: Clears the content of the operand, setting it to zero.
  - Example: `clr r1` – Clears the content of register `r1`.
- **not**: Inverts all bits of the operand.
  - Example: `not r1` – Inverts all bits in register `r1`.
- **inc**: Increments the content of the operand by one.
  - Example: `inc r1` – Increments the value in register `r1` by 1.
- **dec**: Decrements the content of the operand by one.
  - Example: `dec C` – Decrements the value of the label `C` by 1.
- **jmp**: Unconditionally jumps to the address specified by the operand.
  - Example: `jmp LINE` – Jumps to the address labeled `LINE`.
- **bne**: Branches to the specified address if the Z flag in the PSW is not set.
  - Example: `bne LINE` – Branches to `LINE` if the Z flag is clear.
- **red**: Reads a character from standard input and stores it in the operand.
  - Example: `red r1` – Reads a character from stdin and stores it in register `r1`.
- **prn**: Prints the content of the operand to standard output.
  - Example: `prn r1` – Prints the value in register `r1` to stdout.
- **jsr**: Jumps to a subroutine, saving the return address on the stack.
  - Example: `jsr FUNC` – Calls subroutine `FUNC` and saves the return address.

<!-- Third Group: No-Operand Opcodes -->
<h3 id="third-group-no-operand-opcodes">🤟 Third Group: No-Operand Opcodes</h3>

These instructions do not require any operands:

- **rts**: Returns from a subroutine by popping the return address from the stack into the Program Counter (PC).
  - Example: `rts` – Returns from the current subroutine.
- **stop**: Stops program execution.
  - Example: `stop` – Halts the execution of the program.

<!-- Assembly Language Syntax -->
<h2 id="assembly-language-syntax">✍️ Assembly Language Syntax</h2>

Write your assembly code with these cool features:

<!-- Macros -->
<h3 id="macros">🗃️ Macros</h3>

Define macros with macr <macro_name>, include a series of instructions, and close with endmacr. This helps to simplify repetitive code.

Example:

```assembly
macr myMacro
    mov r1, r2
    add r3, r4
endmacr
```

<!-- Directives -->
<h3 id="directives">🗒️ Directives</h3>

Use special commands like `.entry`, `.extern`, and more to manage your code's structure.

Example:

```assembly
.extern start
.entry end
.string "abcd"
.data 1, -5, 0
```

<!-- Instructions -->
<h3 id="instructions">🗺️ Instructions</h3>

Use our supported opcodes to perform operations in your assembly code. Each opcode corresponds to a specific machine instruction.

Example:

```assembly
mov r1, r2
add r3, r4
jmp start
```

<!-- Variables (Labels) -->
<h3 id="variables-labels">❓ Variables (Labels)</h3>

Define and use variables in your code.

Example:

```assembly
var: .data 3
```

Each instruction and operation is carefully designed to give you complete control over your assembly code, allowing you to write efficient and functional programs.

<!-- Addressing Methods (Modes) -->
<h2 id="addressing-methods-modes">📌 Addressing Methods (Modes)</h2>

Understanding the addressing methods used in our assembler is key to writing effective assembly code. Here’s a breakdown of the supported addressing methods:

Our assembler supports four addressing methods, labeled as 0, 1, 2, and 3.

- **(0) Immediate Addressing:**
  - Format: `#number`
  - In this mode, the operand is a constant value. For example, mov #5, r1 loads the value 5 directly into register r1.
- **(1) Direct Addressing:**
  - Format: `label`
  - This mode uses a direct reference to a memory location. For example, mov label, r2 moves the value stored at label into register r2.
- **(2) Indirect Addressing:**
  - Format: `*register`
  -  This method accesses memory indirectly through a register. For example, mov *r3, r4 moves the value pointed by r3 into r4.
- **(3) Indexed Addressing:**
  - Format: `register`
  - This method accesses the value of a base register. For instance, mov r5, r6 loads the value from the memory location of r5 into r6.

Each addressing method allows for flexible data manipulation, enabling you to write efficient and powerful assembly code.

<!-- Addressing Methods for Operations -->
<h2 id="addressing-methods-for-operations">⚙️ Addressing Methods for Operations</h2>

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

<!-- First Word Encoding -->
<h2 id="first-word-encoding">👨‍💻 First Word Encoding</h2>

In our assembler project, instruction encoding is done in the first word of the machine instruction. Here's a breakdown of how the encoding works:

<!-- Opcodes (Bits 14-11) -->
<h3 id="opcodes">➕ Opcodes (Bits 14-11)</h3>

- The opcode is represented by bits 14-11 of the first word in the instruction. Each opcode corresponds symbolically to an assembly operation name, and these operation names are always written in lowercase.

<!-- Source Operand (Bits 10-7) -->
<h3 id="source-operand">🏁 Source Operand (Bits 10-7)</h3>

- These bits encode the addressing method for the source operand. Each addressing method has a dedicated bit:
  - If the source operand is provided in this method, the corresponding bit is set to 1.
  - Otherwise, the bit is set to 0.
- If the instruction does not have a source operand, all four bits are cleared to 0.

<!-- Destination Operand (Bits 6-3) -->
<h3 id="destination-operand">🚩 Destination Operand (Bits 6-3)</h3>

- Similar to the source operand, these bits encode the addressing method for the destination operand:
  - A bit is set to 1 if the destination operand is provided in this method.
  - Otherwise, the bit is set to 0.
- If the instruction does not have a destination operand, all four bits are cleared to 0.

<!-- A,R,E Field (Bits 2-0) -->
<h3 id="a-r-e-field">✈️ A,R,E Field (Bits 2-0)</h3>

- This field characterizes the role of the A, R, E bits in the machine code:
  - The A bit is always set to 1 in the first word of every instruction.
  - The R and E bits are set to 0.
- This field is added to each word in the instruction's encoding.

Further information about the A,R,E field will be provided later. However, If you’d like to explore this information right away, you can refer to [The A,R,E Field Encoding](https://github.com/talfig/Assembler/blob/main/README.md#the-a-r-e-field-encoding) section for more details.

For a detailed breakdown of how the bits are allocated, see the table below:

| 14  | 13  | 12  | 11  | 10  |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----|----|----|
| Opcode |||| Source operand |||| Destination operand |||| The field A,R,E |||
| MSB | Third bit | Second bit | LSB | Method 3 | Method 2 | Method 1 | Method 0 | Method 3 | Method 2 | Method 1 | Method 0 |  A  |  R  |  E  |

<!-- Addressing Methods Encoding -->
<h2 id="addressing-methods-encoding">🧠 Addressing Methods Encoding</h2>

Addressing methods often require additional words in the machine code for each operand.

When an instruction contains two operands, the additional word for the source operand is encoded first, followed by the word for the destination operand. There is a special case where both operands are encoded using a single shared word.

<!-- Immediate Addressing -->
<h3 id="immediate-addressing">⚡ Immediate Addressing</h3>

- **Operand Representation:** The operand itself, which is a 12-bit two's complement integer, is contained in bits 14-3 of the word.
- **A,R,E Bits:** In immediate addressing, the `A` bit is set to 1, and the other two bits (`R`, `E`) are set to 0.

<!-- Direct Addressing -->
<h3 id="direct-addressing">🏹 Direct Addressing</h3>

- **Operand Representation:** The operand is a memory address, with the word at this address in memory being the operand. The address is represented as a 12-bit unsigned number in bits 14-3 of the word.
- **A,R,E Bits:** 
  - If the address is internal (i.e., within the current source file), the `R` bit is set to 1, and the `A` and `E` bits are set to 0.
  - If the address is external (i.e., from another source file), the `E` bit is set to 1, and the `A` and `R` bits are set to 0.

<!-- Indirect Register Addressing -->
<h3 id="indirect-register-addressing">📲 Indirect Register Addressing</h3>

- **Operand Representation:** Accesses memory through a pointer in a register. The content of the register is a memory address, and the word at this address is the operand. The address is represented as a 15-bit unsigned number in the register.
- **A,R,E Bits:** In indirect register addressing, the `A` bit is set to 1, and the other two bits (`R`, `E`) are set to 0.
- **Register Coding:**
  - If the operand is a destination, bits 5-3 of the word contain the register number used as a pointer.
  - If the operand is a source, bits 8-6 of the word contain the register number used as a pointer.
  - If there are two operands using indirect register addressing, both registers share the same word, with bits 5-3 containing the destination register and bits 8-6 containing the source register.

<!-- Direct Register Addressing -->
<h3 id="direct-register-addressing">🚪 Direct Register Addressing</h3>

- **Operand Representation:** The operand is a direct register.
- **A,R,E Bits:** In direct register addressing, the `A` bit is set to 1, and the other two bits (`R`, `E`) are set to 0.
- **Register Coding:**
  - If the register is a destination, bits 5-3 of the word contain the register number.
  - If the register is a source, bits 8-6 of the word contain the register number.
  - If there are two operands using either direct register or indirect register addressing, both registers share the same word, with bits 5-3 containing the destination register and bits 8-6 containing the source register.

<!-- Unused Bits -->
<h3 id="unused-bits">🗑️ Unused Bits</h3>

- Any bits in the instruction word that are not used should be set to 0.

<!-- Types of Statements in Assembly Language -->
<h2 id="types-of-statements-in-assembly-language">📚 Types of Statements in Assembly Language</h2>

The maximum length of a line in the source file is 80 characters (excluding the 
newline character `\n`).

Assembly language typically includes four types of statements:

| **Statement Type**    | **Explanation**                                                                                                  |
|-----------------------|------------------------------------------------------------------------------------------------------------------|
| **Empty Statement**    | A line that contains only whitespace (spaces, tabs, etc.). Essentially, it does nothing and will be ignored during compilation. |
| **Comment Statement**  | A line beginning with a semicolon `;` which is used to comment out code or add explanations in the assembly source. These are also ignored by the assembler. |
| **Instruction Statement** | A line containing valid assembly code that the assembler will translate into machine language. These lines typically contain an opcode and operands. |
| **Directive Statement**  | A line that starts with a dot `.` followed by a directive keyword (e.g., `.entry`, `.extern`). These lines instruct the assembler on how to process the subsequent code. |

<!-- Directive Statements -->
<h2 id="directive-statements">🧰 Directive Statements</h2>

<!-- .data Directive -->
<h3 id="data-directive">📊 ".data" Directive</h3>

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

<!-- .string Directive -->
<h3 id="string-directive">📑 ".string" Directive</h3>

- The `.string` instruction allocates space in the data image to store a string.
- Parameters: A single legal string enclosed in double quotes.

Example:

```assembly
STR: .string "abcdef"
```
The string "abcdef" is stored in the data image with each character in a separate word, followed by a `0` to indicate the end of the string. The label `STR` refers to the address of the first character.

<!-- .entry Directive -->
<h3 id="entry-directive">📥 ".entry" Directive</h3>

- The `.entry` instruction identifies a label that can be referenced from other assembly source files.
- Parameters: A single label name defined in the current source file.

Example:

```assembly
.entry HELLO
```

This instruction marks the label HELLO as available for external reference.

<!-- .extern Directive -->
<h3 id="extern-directive">🌐 ".extern" Directive</h3>

- The `.extern` instruction indicates that a label is defined in another source file.
- Parameters: A single label name that is defined externally.

Example:

```assembly
.extern HELLO
```

This indicates that the label HELLO is defined in another source file and will be linked accordingly.

<!-- Instruction Fields -->
<h2 id="instruction-fields">🛑 Instruction Fields</h2>

<!-- Labels -->
<h3 id="labels">🏷️ Labels</h3>

- A label is a symbolic representation of an address in memory.
- Syntax:
  -  Maximum length: 31 characters.
  -  Format: Ends with a colon `:`, which must be directly attached to the label name without spaces.
  -  Usage: After a label, there must be an instruction or directive. Labels cannot stand alone.

Example:

```assembly
Hello: .data 1, 2
X: mov r1, r2
He3: .string "abcd"
```

Labels are case-sensitive and must be unique within the same file.

> Note: A label defined at the beginning of a line with `.entry` or `.extern` directives is meaningless and will be ignored by the assembler.

<!-- Numbers -->
<h3 id="numbers">🔢 Numbers</h3>

- Legal numbers are decimal integers that can be positive or negative.

Example:

```assembly
123, -57, +17
```

<!-- Strings -->
<h3 id="strings">🔠 Strings</h3>

- A legal string is a sequence of printable ASCII characters enclosed in double quotes.

Example:

```assembly
"hello world"
```

<!-- Instruction Statement Formats -->
<h2 id="instruction-statement-formats">📋 Instruction Statement Formats</h2>

<!-- Two-Operand Instruction -->
<h3 id="two-operand-instruction">2️⃣ Two-Operand Instruction</h3>

- Format: `label: opcode source-operand, target-operand`

Example:

```assembly
HELLO: add r7, B
```

<!-- One-Operand Instruction -->
<h3 id="one-operand-instruction">1️⃣ One-Operand Instruction</h3>

- Format: `label: opcode target-operand`

Example:

```assembly
HELLO: bne XYZ
```

<!-- No-Operand Instruction -->
<h3 id="no-operand-instruction">0️⃣ No-Operand Instruction</h3>

- Format: `label: opcode`

Example:

```assembly
END: stop
```

<!-- The A,R,E Field Encoding -->
<h2 id="the-a-r-e-field-encoding">🔍 The A,R,E Field Encoding</h2>

In every machine code instruction (not data), the assembler inserts specific information into the A, R, E field to facilitate the linking and loading process. This field contains three bits: A, R, and E, which indicate how the word should be treated when the program is loaded into memory for execution. The assembler initially generates code as if it were to be loaded at a start address. The information in these bits allows the code to be relocated to any address in memory without requiring reassembly.

<!-- The A,R,E Bits -->
<h2 id="the-a-r-e-bits">📡 The A,R,E Bits</h2>

- **A (Absolute):** 
  - If the A bit is set to 1, it means the word's content is independent of the memory location where the program is loaded during execution (e.g., an immediate operand).
- **R (Relocatable):**
  - If the R bit is set to 1, it indicates that the word's content depends on the actual memory location where the program will be loaded (e.g., an internal label address).
- **E (External):**
  - If the E bit is set to 1, the word's content is dependent on the value of an external symbol (e.g., a label defined in another source file).

These bits are set according to the addressing modes used and the location of the symbols within the program, ensuring that the final machine code is adaptable for different memory layouts during execution.

For comprehensive details on the linking and loading stage, please see the [Linking and Loading](https://github.com/talfig/Assembler/blob/main/README.md#linking-and-loading) section in the appendix.

<!-- Macro Handling -->
<h2 id="macro-handling">📐 Macro Handling</h2>

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

<!-- Assembler with Two Passes -->
<h2 id="assembler-with-two-passes">🔁 Assembler with Two Passes</h2>

In the first pass of the assembler, the program reads the assembly code to determine the symbols (labels) appearing in the program, assigns an address to each symbol, and builds the symbol table. In the second pass, using the symbol table, the assembler generates the actual machine code.

Our assembler handles the following instructions during the second pass: `mov`, `jmp`, `prn`, `sub`, `cmp`, `inc`, `bne`, `stop`. The corresponding machine code is generated based on the opcode and the operands provided.

Additionally, the assembler should replace the symbols `K`, `STR`, `LIST`, `MAIN`, `LOOP`, `END` with the memory addresses where each corresponding data or instruction is located.

<!-- First Pass -->
<h3 id="first-pass">📈 First Pass</h3>

In the first pass, rules are required to determine the address to be assigned to each symbol. The basic principle is to count the memory locations occupied by the instructions. If each instruction is loaded into memory at the location following the previous instruction, such counting will indicate the address of the next instruction. This counting is performed by the assembler and is maintained in the instruction counter (IC). The initial value of IC is 100 (decimal), so the machine code of the first instruction is constructed to load into memory starting from address 100. The IC is updated with each instruction line that allocates space in memory. After the assembler determines the length of the instruction, the IC is increased by the number of cells (words) occupied by the instruction, and thus it points to the next available cell.

The assembler reads the list of numbers, which appears after the `.data` directive, inserts each number into the data array, and advances the data pointer `DC` (Data Counter) by one for each number inserted.

If the line with the `.data` directive contains a label, this label is inserted into the symbol table with the value of `DC` before inserting the numbers. The label is marked as relocatable and flagged to indicate that the definition is in the data section.

At the end of the first pass, all labels associated with the data section are updated by adding the final value of `IC` (Instruction Counter) to their addresses. This adjustment is required because in the machine code image, the data section comes after the instructions. Therefore, the addresses of data labels must be shifted by the total number of instruction words, which is `IC`.

We divide the machine code into two regions:
- **Instruction region (code)**, tracked by `IC`
- **Data region (data)**, tracked by `DC`

Each region maintains its own counter:
- `IC` is initialized to 100 (decimal), representing the starting memory address for the code.
- `DC` is initialized to 0, and it increases with every `.data` or `.string` directive.

The memory layout after assembly is as follows:

```
[ Address 100        ] -> First instruction  
[ ...                ] -> Instruction region  
                       (length = IC - 100)
[ Address 100 + IC   ] -> First data element  
[ ...                ] -> Data region  
                       (length = DC)
```

As mentioned, to encode instructions in machine language, the assembler maintains a table that contains a corresponding code for each operation name. During translation, the assembler replaces each operation name with its code, and each operand is replaced with its corresponding encoding. However, this replacement process is not so simple. The instructions use various addressing methods for operands. The same operation can have different meanings in each addressing method, and therefore different encodings are applied depending on the addressing methods. For example, the `mov` operation can refer to copying the content of a memory cell to a register or copying the content of one register to another, and so on. Each such possibility of `mov` might have a different encoding.

The assembler needs to scan the entire instruction line and decide on the encoding based on the operands. Typically, the encoding is divided into a field for the operation name and additional fields containing information about the addressing methods. All fields together require one or more words in the machine code.

When the assembler encounters a label at the beginning of the line, it recognizes it as a label definition and assigns it an address, which is the current content of the IC. Thus, all labels receive their addresses at the time of definition. These labels are entered into the symbol table, which, in addition to the label name, contains the address and additional attributes. When a label is referred to in the operand of any instruction, the assembler can retrieve the corresponding address from the symbol table.

An instruction can also refer to a symbol that has not yet been defined in the program but will be defined later. For example, consider a branch instruction to an address defined by the label `A` that appears later in the code:

```assembly
bne A
...
A: ...
```

<!-- Second Pass -->
<h3 id="second-pass">📉 Second Pass</h3>

As seen in the first pass, the assembler cannot construct the machine code of operands using symbols that have not yet been defined. Only after the assembler has scanned the entire program, so that all symbols have already been entered into the symbol table, can the assembler complete the machine code of all operands.

To achieve this, the assembler performs a second pass over the source code. During this pass, it updates the machine code for operands by substituting the symbols with their corresponding values from the symbol table. By the end of this second pass, the entire program is fully translated into machine code.

<!-- Input and Output Files -->
<h2 id="input-and-output-files">🖨️ Input and Output Files of the Assembler</h2>

When running the assembler, command line arguments should include a list of source file names (one or more). These are text files containing programs written in the assembly language defined for this project.

The assembler processes each source file separately and generates the following output files:

- **`.am` file**: Contains the source file after the pre-assembler stage (after macro expansion).
- **`.ob` file**: Contains the machine code.
- **`.ext` file**: Includes details of all locations (addresses) in the machine code where an external symbol (declared with the `.extern` directive) is used.
- **`.ent` file**: Includes details of all symbols declared as entry points (declared with the `.entry` directive).

If the source file does not contain any `.extern` directives, the assembler will not create an `.ext` file. Similarly, if there are no `.entry` directives, an `.ent` file will not be generated.

Source file names must have the `.as` extension. For example, `hello.as`, `x.as`, and `y.as` are valid names. When passing these file names as arguments to the assembler, the extension is omitted.

Example:

```bash
./assembler x y hello
```

<!-- Object File Format -->
<h3 id="object-file-format">🖼️ Object File Format</h3>

The assembler constructs a memory image where the encoding of the first instruction from the assembly file is placed at address 100 (in decimal) in memory. The encoding of the second instruction is placed at the address following the first instruction (depending on the number of words in the first instruction), and so on until the last instruction.

Immediately after the encoding of the last instruction, the assembler places the encoding of the data created by `.data`, `.string`, and other data directives into the memory image. The data will be placed in the order it appears in the source file. An operand of an instruction referring to a symbol defined in the same file will be encoded to point to the appropriate location in the memory image created by the assembler.

Note that variables appear in the memory image after the instructions. This is why it is necessary to update the symbol table, at the end of the first pass, with the values of symbols defining data (symbols of type `.data`).

An object file fundamentally contains the described memory image. An object file is composed of text lines as follows:

- The first line of the object file is the "header," which contains two decimal numbers: the total length of the instruction section (in memory words) followed by the total length of the data section (in memory words). There is one space between the two numbers.

- The following lines in the file contain the memory image. Each line contains two values: the address of a memory word and the content of that word. The address is written in decimal, padded to four digits (including leading zeros), and the content is written in octal, padded to five digits (including leading zeros). There is one space between the two values on each line.

<!-- Entries File Format -->
<h3 id="entries-file-format">🏠 Entries File Format</h3>

The entries file is composed of text lines. Each line contains the name of a symbol defined as an entry and its value, as found in the symbol table. The values are represented in decimal format.

The order of the labels in the file does not matter.

<!-- Externals File Format -->
<h3 id="externals-file-format">🌍 Externals File Format</h3>

The externals file is also composed of text lines. Each line contains the name of a symbol defined as external and an address in machine code where an operand referring to this symbol is encoded. It is possible that there are multiple addresses in the machine code referring to the same external symbol. Each such reference will have a separate line in the externals file. The addresses are represented in decimal format.

Like in the Entries file, the order of the labels in the file does not matter.

<!-- Example Program -->
<h2 id="example-program">📜 Example Program</h2>

Here’s a quick demo of an assembly program in action:

Pre-assembler program:

```assembly
; file example.as 
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

Below is the full binary encoding table obtained from the source file, followed by the output file formats.

| Decimal Address | Source Code        | Explanation                             | Binary Machine Code  |
|-----------------|--------------------|-----------------------------------------|----------------------|
| 0100            | MAIN: add r3, LIST  | First word of instruction               | 001010000010100       |
| 0101            |                     | Source register 3                       | 000000011000100       |
| 0102            |                     | Address of label LIST                   | 000010001001010       |
| 0103            | jsr fn1             |                                         | 110100000010100       |
| 0104            |                     | Address of label fn1 (external)         | 000000000000001       |
| 0105            | LOOP: prn #48       |                                         | 110000000001100       |
| 0106            |                     | Immediate value 48                      | 000000110000100       |
| 0107            | lea STR, r6         |                                         | 010000101000100       |
| 0108            |                     | Address of label STR                    | 000010000100010       |
| 0109            |                     | Target register 6                       | 000000000110100       |
| 0110            | inc r6              |                                         | 011100001000100       |
| 0111            |                     | Target register 6                       | 000000000110100       |
| 0112            | mov *r6, L3         |                                         | 000001000010100       |
| 0113            |                     | Source register 6                       | 000000110000100       |
| 0114            |                     | Address of label L3 (external)          | 000000000000001       |
| 0115            | sub r1, r4          |                                         | 001110001000100       |
| 0116            |                     | Source register 1 and target register 4 | 000000001100100       |
| 0117            | cmp r3, #-6         |                                         | 000110000001100       |
| 0118            |                     | Source register 3                       | 000000011000100       |
| 0119            |                     | Immediate value -6                      | 111111111010100       |
| 0120            | bne END             |                                         | 101000000010100       |
| 0121            |                     | Address of label END                    | 000010000011010       |
| 0122            | add r7, *r6         |                                         | 001010000100100       |
| 0123            |                     | Source register r0 and target register 6| 000000111110100       |
| 0124            | clr K               |                                         | 010100000010100       |
| 0125            |                     | Address of label K                      | 000010001100010       |
| 0126            | sub L3, L3          |                                         | 001100100010100       |
| 0127            |                     | Address of label L3 (external)          | 000000000000001       |
| 0128            |                     | Address of label L3 (external)          | 000000000000001       |
| 0129            | jmp LOOP            |                                         | 100100000010100       |
| 0130            |                     | Address of label LOOP                   | 000001101001010       |
| 0131            | END: stop           |                                         | 111100000000100       |
| 0132            | STR: .string "abcd" | Ascii code 'a'                          | 000000001100001       |
| 0133            |                     | Ascii code 'b'                          | 000000001100010       |
| 0134            |                     | Ascii code 'c'                          | 000000001100011       |
| 0135            |                     | Ascii code 'd'                          | 000000001100100       |
| 0136            |                     | Ascii code '\0' (end of string)         | 000000000000000       |
| 0137            | LIST: .data 6, -9   | Integer 6                               | 000000000000110       |
| 0138            |                     | Integer -9                              | 111111111110111       |
| 0139            | .data -100          | Integer -100                            | 111111110011100       |
| 0140            | K: .data 31         | Integer 31                              | 000000000011111       |

**Object file:**

```ob
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

**Entries file:**

```ent
LIST 0137
MAIN 0100
```

**Externals file:**

```ext
fn1 0104
L3 0114
L3 0127
L3 0128
```

<!-- Installation -->
<h2 id="installation">🛠️ Installation</h2>

Ready to build? Follow the appropriate steps according to your operating system:

<!-- Linux -->
<h3 id="linux"> 🐧 Linux</h3>

**1.** Open your terminal.

**2.** Clone this repository with:

```bash
git clone https://github.com/talfig/Assembler.git
```

**3.** Ensure you have a C compiler installed.

Run the following command to check if GCC is installed:

```bash
gcc --version
```

If you prefer Clang, you can check its installation with:

```bash
clang --version
```

<!-- GitHub Codespaces -->
<h3 id="github-codespaces"> ☁️ GitHub Codespaces</h3>

**1.** Go to your GitHub repository.

**2.** Click on the Code button and select Create codespace on main.

**3.** Once the Codespace is ready, open the terminal within the Codespace.

**4.** (Optional) Customize the Codespace environment for Ubuntu by adding a .devcontainer/devcontainer.json file with the following content:

```json
{
  "name": "Ubuntu Development Environment",
  "image": "mcr.microsoft.com/vscode/devcontainers/base:ubuntu",
  "features": {
    "docker-from-docker": "latest"
  },
  "extensions": [
    "ms-vscode.cpptools",
    "golang.go"
  ]
}
```

This configuration sets up an Ubuntu-based environment with the necessary tools installed.

---

After setting up your environment, Navigate to the project directory where the `Makefile` is located using:

```bash
cd Assembler
```

Replace `Assembler` with the actual name of the directory if it differs.

Move the `Makefile` from the `Build` directory to the `Assembler` directory:

```bash
mv Build/Makefile .
```

Finally, Run the make command to compile the project and build the assembler:

```bash
make
```

The make command will read the `Makefile` and execute the specified build instructions to compile the code and link the object files into an executable.

After the build process is complete, you should see the assembler executable in the project directory.

<!-- Usage -->
<h2 id="usage">🎯 Usage</h2>

To run the assembler on a certain file:

```bash
./assembler <source_file>
```

Replace <source_file> with the path to your assembly code file. To process multiple files, list each file separated by spaces:

```bash
./assembler <source_file1> <source_file2> ...
```

<!-- Error Handling -->
<h2 id="error-handling">⚠️ Error Handling</h2>

Bumped into issues? No worries! Our assembler offers descriptive error messages such as:

- **Memory allocation failure:** Indicates a problem with allocating the necessary memory resources.
- **Unrecognized commands:** Shows when the assembler encounters commands it doesn’t understand.
- **Syntax errors:** Flags errors in the syntax of your assembly code.
- **File errors:** It usually means the file could not be found or accessed. Check the file path and ensure you have the necessary permissions.

<!-- Directory Structure -->
<div style="font-family: Arial, sans-serif; color: #333; background-color: #f9f9f9; border: 1px solid #ddd; border-radius: 5px; padding: 20px; max-width: 700px; margin: auto;">
    <h2 id="directory-structure" style="color: #00c4cc;">📁 Directory Structure</h2>
    <p>The project is organized as follows:</p>
    <ul style="list-style-type: none; padding: 0;">
        <li>
            <strong style="color: #00c4cc;">📁 Build</strong>
            <p style="margin: 0; padding: 0 0 10px 20px;">Contains build scripts and configuration files.</p>
            <ul style="list-style-type: none; padding-left: 20px;">
                <li>Makefile</li>
                <li>CMakeLists.txt</li>
            </ul>
        </li>
        <li>
            <strong style="color: #00c4cc;">📁 HeaderFiles</strong>
            <p style="margin: 0; padding: 0 0 10px 20px;">Contains header files for the project.</p>
            <ul style="list-style-type: none; padding-left: 20px;">
                <li>first_pass.h</li>
                <li>second_pass.h</li>
                <li>...</li>
            </ul>
        </li>
        <li>
            <strong style="color: #00c4cc;">📁 InvalidInputs</strong>
            <p style="margin: 0; padding: 0 0 10px 20px;">Contains input files that are expected to cause errors.</p>
            <ul style="list-style-type: none; padding-left: 20px;">
                <li>broken_program1.as</li>
                <li>broken_program2.as</li>
                <li>...</li>
            </ul>
        </li>
        <li>
            <strong style="color: #00c4cc;">📁 InvalidOutputs</strong>
            <p style="margin: 0; padding: 0 0 10px 20px;">Contains output files corresponding to invalid inputs.</p>
            <ul style="list-style-type: none; padding-left: 20px;">
                <li><strong style="color: #00c4cc;">📁 broken_program1</strong>
                  <ul style="list-style-type: none; padding-left: 20px;">
                    <li>broken_program1.txt</li>
                  </ul>
                </li>
                <li><strong style="color: #00c4cc;">📁 broken_program2</strong>
                  <ul style="list-style-type: none; padding-left: 20px;">
                    <li>broken_program2.txt</li>
                  </ul>
                </li>
                <li>...</li>
            </ul>
        </li>
        <li>
            <strong style="color: #00c4cc;">📁 SourceFiles</strong>
            <p style="margin: 0; padding: 0 0 10px 20px;">Contains the source code files.</p>
            <ul style="list-style-type: none; padding-left: 20px;">
                <li>assembler.c</li>
                <li>first_pass.c</li>
                <li>...</li>
            </ul>
        </li>
        <li>
            <strong style="color: #00c4cc;">📁 ValidInputs</strong>
            <p style="margin: 0; padding: 0 0 10px 20px;">Contains input files that should be processed correctly.</p>
            <ul style="list-style-type: none; padding-left: 20px;">
                <li>fibonacci.as</li>
                <li>text_encryption.as</li>
                <li>...</li>
            </ul>
        </li>
        <li>
            <strong style="color: #00c4cc;">📁 ValidOutputs</strong>
            <p style="margin: 0; padding: 0 0 10px 20px;">Contains output files corresponding to valid inputs.</p>
            <ul style="list-style-type: none; padding-left: 20px;">
                <li><strong style="color: #00c4cc;">📁 fibonacci</strong>
                  <ul style="list-style-type: none; padding-left: 20px;">
                    <li>fibonacci.am</li>
                    <li>fibonacci.ob</li>
                    <li>fibonacci.ent</li>
                    <li>fibonacci.ext</li>
                  </ul>
                </li>
                <li><strong style="color: #00c4cc;">📁 text_encryption</strong>
                  <ul style="list-style-type: none; padding-left: 20px;">
                    <li>text_encryption.am</li>
                    <li>text_encryption.ob</li>
                    <li>text_encryption.ent</li>
                    <li>text_encryption.ext</li>
                  </ul>
                </li>
                <li>...</li>
            </ul>
        </li>
    </ul>
</div>

<!-- Appendix -->
<h2 id="appendix"> 📘 Appendix </h2>

<!-- Program Status Word (PSW) -->
<h3 id="program-status-word-psw">🚦 Program Status Word (PSW)</h3>

The Program Status Word (PSW) is a special register in the CPU that contains flags and control bits reflecting the state of the processor. These flags are typically affected by the execution of arithmetic and logic instructions. The PSW is used to determine the outcome of conditional operations and to control the flow of the program.

Common Flags in the PSW:

- **Z (Zero) Flag**: 
  - Set to `1` if the result of an operation is zero.
  - Cleared (`0`) if the result is non-zero.
  
- **N (Negative) Flag**: 
  - Set if the result of an operation is negative.
  
- **C (Carry) Flag**: 
  - Set if an arithmetic operation generates a carry out of or a borrow into the high-order bit.
  
- **V (Overflow) Flag**: 
  - Set if an arithmetic operation results in an overflow, meaning the result is too large to be represented in the destination operand.

The flags in the PSW are often used by conditional branch instructions to make decisions based on the result of a previous operation. For example:

- **bne (branch if not equal)**: This instruction checks the Z flag; if the Z flag is `0` (indicating that the previous operation did not result in zero), the program will branch to the address specified by the operand.

<!-- Linking and Loading -->
<h3 id="linking-and-loading">🧲 Linking and Loading</h3>

When working with assembly language, the process of transforming your code into a fully functioning executable program involves more than just the work of the assembler. Two additional critical steps, linking and loading, ensure that your program is correctly integrated with other modules and loaded into memory for execution.

<!-- Linking -->
<h4 id="linking">🔗 Linking</h4>

Linking is the process of combining multiple object files generated by the assembler into a single executable file. Here's how it works:

- **Object Files:** When you assemble your source code, the assembler generates object files. These files contain the machine code for each module of your program, along with necessary metadata such as symbol tables and relocation information.
  
- **Symbol Resolution:** During linking, the linker resolves references between object files. For instance, if one module references a function or variable defined in another, the linker connects these references by identifying their memory addresses.

- **Relocation:** The linker adjusts memory addresses within object files to create a single continuous memory space. This step ensures that all modules work together seamlessly, with correct address references.

- **Executable File Creation:** After resolving symbols and performing relocation, the linker combines all object files into a single executable file. This file can then be loaded into memory for execution.

<!-- Loading -->
<h4 id="loading">⏳ Loading</h4>

Loading is the final step before your program runs on the CPU. The loader is responsible for placing the executable file into the computer's memory. Here's what happens:

- **Memory Allocation:** The loader allocates memory space for the program based on the executable file's specifications. This includes allocating space for code, data, and stack segments.

- **Loading into Memory:** The loader copies the executable's code and data into the allocated memory space. It also initializes registers and the program counter (PC) to point to the start of the program.

- **Dynamic Linking (Optional):** In some systems, dynamic linking occurs at this stage. This involves linking to shared libraries that are not included in the executable file but are available in the system. The loader resolves references to these external libraries and loads them into memory as needed.

- **Program Execution:** Once loading is complete, the CPU begins executing the program by reading instructions from memory, starting at the program counter's address.

<!-- License -->
<h2 id="license">© License</h2>

This project is licensed under the GNU Affero General Public License v3.0 (AGPL) - see the [LICENSE](https://github.com/talfig/Assembler/blob/main/LICENSE) file for details.

<!-- Contact -->
<h2 id="contact">📬 Contact </h2>

<div align="left">
  <table>
    <tr>
      <td align="center">
        <a href="https://www.linkedin.com/in/talfig/" target="_blank">
          <img src="https://upload.wikimedia.org/wikipedia/commons/c/ca/LinkedIn_logo_initials.png" alt="LinkedIn" width="80" height="80">
          <br>
          LinkedIn
        </a>
      </td>
      <td align="center">
        <a href="mailto:talfigw@gmail.com" target="_blank">
          <img src="https://upload.wikimedia.org/wikipedia/commons/4/4e/Mail_%28iOS%29.svg" alt="Email" width="80" height="80">
          <br>
          Email
        </a>
      </td>
    </tr>
  </table>
</div>

<p align="center">
  <img src="https://raw.githubusercontent.com/talfig/talfig/main/gratitude.svg" alt="Gratitude Image">
</p>
