cmake_minimum_required(VERSION 3.27)
project(Assembler C)

set(CMAKE_C_STANDARD 90)

# Add -pedantic and additional warning flags
add_compile_options(-ansi -Wall -pedantic)


add_executable(Assembler assembler.c
        macr.h
        macr.c
        preprocessor.c
        preprocessor.h
        errors.c
        errors.h
        token_utils.c
        token_utils.h
        label.h
        label.c
        globals.h
        globals.c
        first_pass.c
        first_pass.h
        integer_utils.c
        integer_utils.h
        opcode_utils.c
        opcode_utils.h
        second_pass.c
        second_pass.h
        file_utils.c
        file_utils.h
)
