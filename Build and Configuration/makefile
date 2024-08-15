# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -ansi -pedantic
DEBUG = -g

# Executable name
TARGET = Assembler

# Source files
SRCS = assembler.c \
       macr.c \
       preprocessor.c \
       token_utils.c \
       errors.c \
       globals.c \
       label.c \
       first_pass.c \
       second_pass.c \
       opcode_utils.c \
       integer_utils.c \
       file_utils.c

# Object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Default rule (first rule is the default target)
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to create object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Debug target
debug: CFLAGS += $(DEBUG)
debug: clean all

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (not actual files)
.PHONY: all clean debug
