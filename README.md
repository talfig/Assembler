<h1 align="center">🔧 Assembler: The Code Converter</h1>

<p align="center">
  Welcome to the ultimate assembler built in C! Transform your assembly code into machine language with flair and precision.
  <br>
  🚀 Custom Assembly Language | 🛠️ Macro Magic | 💡 Detailed Error Reporting
</p>

## 🚀 Features

- **Custom Assembly Language:** Dive into our unique assembly language with a defined set of opcodes.
- **Macro Wizardry:** Create and use powerful macros to streamline your assembly code.
- **Smart Error Handling:** Get detailed, compiler-like error messages to troubleshoot with ease.

## 🧩 Supported Opcodes

Our assembler brings to life a variety of opcodes for your coding pleasure:

- `mov` (0) – Move data
- `cmp` (1) – Compare values
- `add` (2) – Addition
- `sub` (3) – Subtraction
- `lea` (4) – Load effective address
- `clr` (5) – Clear data
- `not` (6) – Bitwise NOT
- `inc` (7) – Increment
- `dec` (8) – Decrement
- `jmp` (9) – Jump to address
- `bne` (10) – Branch if not equal
- `red` (11) – Read input
- `prn` (12) – Print output
- `jsr` (13) – Jump to subroutine
- `rts` (14) – Return from subroutine
- `stop` (15) – Halt execution

## ✍️ Assembly Language Syntax

Write your assembly code with these cool features:

- **Labels:** Define and use labels in your code.
- **Directives:** Use special commands like `.entry`, `.extern`, and more.
- **Macros:** Define macros with `macr <macro_name>`, include instructions, and close with `endmacr`.

## 📌 Addressing Methods
Understanding the addressing methods used in our assembler is key to writing effective assembly code. Here’s a breakdown of the supported addressing methods:

- **Immediate Addressing (#):** In this mode, the operand is a constant value. For example, mov #5, r1 loads the value 5 directly into register r1.
- **Direct Addressing:** This mode uses a direct reference to a memory location. For example, mov var, r2 moves the value stored at var into register r2.
- **Indirect Addressing (with register):** This method accesses memory indirectly through a register. For example, mov *r3, r4 moves the value from the memory address stored in r3 into r4.
- **Indexed Addressing (offset):** This combines a base register with an offset to determine the memory location. For instance, mov r5, r6 loads the value from the memory location of r5 into r6.
Each addressing mode allows for flexible data manipulation, enabling you to write efficient and powerful assembly code.

### 📜 Example Code

Here’s a quick demo of an assembly program in action:

```assembly
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
