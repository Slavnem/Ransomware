# Compiler
CC = g++
CFLAGS = -Iinclude/

# Source
SRC = \
	src/Crypt/Crypt.cpp src/Crypt/Caesar/Caesar.cpp \
	src/FileStream/FileStream.cpp src/FileStream/CFile/CFile.cpp \
	src/Main/Main.cpp

# Object
OBJ = $(SRC:src/%.cpp=build/%.o)

# Target Executable
TARGET = build/Ransomware

# Default Target
all: $(TARGET)

# Link Object Files To Create Final Executable Program
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Compile Each Source File Into Object Files
build/%.o: src/%.cpp
	@mkdir -p build build/Crypt/Caesar build/FileStream/CFile build/Main
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Target To Remove The Files
clean:
	rm -rf build/*

# Phony Targets To Avoid Conflicts With File Names
.PHONY: all clean