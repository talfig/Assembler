# Assembler

## Overview
This project is an assembler written in C. It converts assembly language code into machine code. The assembler supports a specific assembly language that includes various opcodes and directives.

## Features
- **Assembly Language Support:** The assembler handles a custom assembly language with a defined set of opcodes.
- **Macro Handling:** Supports the creation and use of macros within the assembly code.
- **Error Handling:** Provides detailed error messages similar to those seen in compilers.

## Opcodes Supported
The assembler supports the following opcodes:
- `mov` (0)
- `cmp` (1)
- `add` (2)
- `sub` (3)
- `lea` (4)
- `clr` (5)
- `not` (6)
- `inc` (7)
- `dec` (8)
- `jmp` (9)
- `bne` (10)
- `red` (11)
- `prn` (12)
- `jsr` (13)
- `rts` (14)
- `stop` (15)

## Assembly Language Syntax
The assembler uses a specific syntax for writing assembly code, including:
- **Labels:** Labels can be defined and used within the code.
- **Directives:** Special commands like `.entry`, `.extern`, etc.
- **Macros:** The syntax for defining macros is `macr <macro_name>`, followed by instructions, and `endmacr`.

### Example Code
Here is a simple example of an assembly program:

```assembly
start:  mov r1, r2
        add r3, r4
        stop
```

## Installation
Ready to build? Follow these steps:

**1.** Ensure you have a C compiler installed.

**2.** Clone this repository.

**3.** Navigate to the project directory and run:

```bash
make
```

This will compile the assembler and create the executable file.

## Usage
To run the assembler on a certain file:

```bash
./assembler <source_file>
```

Replace <source_file> with the path to your assembly code file.

## Error Handling
Encounter errors? No problem! Our assembler provides descriptive error messages similar to those from compilers:

- **Memory allocation failure**
- **Unrecognized commands**
- **Syntax errors**

## Directory Structure
The project is organized as follows:

- **Build and Configuration:** Contains build scripts and configuration files.
- **Header Files:** Contains header files for the project.
- **Invalid Inputs:** Contains input files that are expected to cause errors.
- **Invalid Outputs:** Contains output files corresponding to invalid inputs.
- **Source Files:** Contains the source code files.
- **Valid Inputs:** Contains input files that should be processed correctly.
- **Valid Outputs:** Contains output files corresponding to valid inputs.
- **Object Files:** Contains object files generated during compilation.
