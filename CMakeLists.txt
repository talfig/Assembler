cmake_minimum_required(VERSION 3.27)
project(mmn14 C)

set(CMAKE_C_STANDARD 90)

# Add -pedantic and additional warning flags
add_compile_options(-ansi -Wall -pedantic)

add_executable(mmn14 main.c
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
        globals.h)
