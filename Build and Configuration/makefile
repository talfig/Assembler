# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -ansi -pedantic -Iheader_files
DEBUG = -g

# Executable name
TARGET = assembler

# Source files directory
SRC_DIR = source_files

# Object files directory
OBJ_DIR = object_files

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files (replace .c with .o, and place them in OBJ_DIR)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule (first rule is the default target)
all: $(TARGET) copy_executable

# Rule to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to copy the executable to both directories
copy_executable:
	@mkdir -p invalid_input valid_input
	@cp $(TARGET) invalid_input/
	@cp $(TARGET) valid_input/

# Rule to create object files in the object_files directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug target
debug: CFLAGS += $(DEBUG)
debug: clean all

# Clean rule to remove generated files
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET) invalid_input/$(TARGET) valid_input/$(TARGET)

# Phony targets (not actual files)
.PHONY: all clean debug copy_executable

