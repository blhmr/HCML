# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Iinclude

# Library
LIB_SRCS = src/hcml_entry.c src/hcml_enums.c src/hcml_file.c src/hcml_handle.c src/hcml_info.c src/hcml_array.c src/hcml_string.c
LIB_OBJS = $(LIB_SRCS:src/%.c=obj/%.o)
	LIB_TARGET = lib/libhcml.a

# Main executable
MAIN_SRC = main.c
MAIN_OBJ = obj/main.o
MAIN_TARGET = bin/main

# Default target
.PHONY: all
all: $(LIB_TARGET) $(MAIN_TARGET)

# Build library
$(LIB_TARGET): $(LIB_OBJS)
	ar rcs $@ $^

# Build main executable
$(MAIN_TARGET): $(MAIN_OBJ) $(LIB_TARGET)
	$(CC) $(CFLAGS) -o $@ $< -Llib -lhcml

# Compile library source files
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile main source file
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

# Install on system
install:
	sudo cp include/hcml.h /usr/include/
	sudo cp lib/libhcml.a /usr/lib/

# Clean
.PHONY: clean
clean:
	rm -f $(LIB_OBJS) $(LIB_TARGET) $(MAIN_OBJ) $(MAIN_TARGET)

