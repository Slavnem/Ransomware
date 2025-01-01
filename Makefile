# Compiler and Flags
CC = g++
CXXFLAGS = -Iinclude/ -O3 -Wall -Wextra -std=c++17 -DMAIN

# Directories
SRC_DIR = src
TEST_DIR = test/25-12-2024-13-36
OBJ_DIR = build/linux

TEST_OBJ_DIR_X86 = $(OBJ_DIR)/test/x86
TEST_OBJ_DIR_X64 = $(OBJ_DIR)/test/x64

RELEASE_OBJ_DIR_X86 = $(OBJ_DIR)/release/x86
RELEASE_OBJ_DIR_X64 = $(OBJ_DIR)/release/x64

# Source Files
SRC = \
    $(SRC_DIR)/Crypt/Crypt.cpp $(SRC_DIR)/Crypt/Caesar/Caesar.cpp $(SRC_DIR)/Crypt/Xor/Xor.cpp \
    $(SRC_DIR)/FileStream/FileStream.cpp $(SRC_DIR)/FileStream/CFile/CFile.cpp \
	$(SRC_DIR)/Ransomware/Ransomware.cpp

MAIN_SRC = $(SRC_DIR)/Main/Main.cpp
TEST_SRC = $(SRC_DIR)/Crypt/Xor/Xor.cpp $(TEST_DIR)/XorTest.cpp
	
# Object Files
TEST_OBJ_X86 = $(TEST_SRC:$(TEST_DIR)/%.cpp=$(TEST_OBJ_DIR_X86)/%.o)
TEST_OBJ_X64 = $(TEST_SRC:$(TEST_DIR)/%.cpp=$(TEST_OBJ_DIR_X64)/%.o)

RELEASE_OBJ_X86 = $(SRC:$(SRC_DIR)/%.cpp=$(RELEASE_OBJ_DIR_X86)/%.o) $(MAIN_SRC:$(SRC_DIR)/%.cpp=$(RELEASE_OBJ_DIR_X86)/%.o)
RELEASE_OBJ_X64 = $(SRC:$(SRC_DIR)/%.cpp=$(RELEASE_OBJ_DIR_X64)/%.o) $(MAIN_SRC:$(SRC_DIR)/%.cpp=$(RELEASE_OBJ_DIR_X64)/%.o)

# Target Executables
TEST_TARGET_X86 = $(TEST_OBJ_DIR_X86)/DebugTest
TEST_TARGET_X64 = $(TEST_OBJ_DIR_X64)/DebugTest

RELEASE_TARGET_X86 = $(RELEASE_OBJ_DIR_X86)/Linsomware
RELEASE_TARGET_X64 = $(RELEASE_OBJ_DIR_X64)/Linsomware

# Default Target
all: release

# Test Target
test: $(TEST_TARGET_X86) $(TEST_TARGET_X64)

$(TEST_TARGET_X86): $(TEST_OBJ_X86)
	@mkdir -p $(dir $@)
	$(CC) -m32 $(CXXFLAGS) $(TEST_OBJ_X86) -o $@

$(TEST_TARGET_X64): $(TEST_OBJ_X64)
	@mkdir -p $(dir $@)
	$(CC) -m64 $(CXXFLAGS) $(TEST_OBJ_X64) -o $@

$(TEST_OBJ_DIR_X86)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -m32 -c $< -o $@

$(TEST_OBJ_DIR_X64)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -m64 -c $< -o $@

# Release Targets
release: $(RELEASE_TARGET_X86) $(RELEASE_TARGET_X64)

$(RELEASE_TARGET_X86): $(RELEASE_OBJ_X86)
	@mkdir -p $(dir $@)
	$(CC) -m32 $(RELEASE_OBJ_X86) -o $@

$(RELEASE_TARGET_X64): $(RELEASE_OBJ_X64)
	@mkdir -p $(dir $@)
	$(CC) -m64 $(RELEASE_OBJ_X64) -o $@

$(RELEASE_OBJ_DIR_X86)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -m32 -c $< -o $@

$(RELEASE_OBJ_DIR_X64)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -m64 -c $< -o $@

# Clean Target To Remove The Files
clean-test:
	rm -rf $(TEST_OBJ_DIR_X86)/ $(TEST_OBJ_DIR_X64)/

clean-release:
	rm -rf $(RELEASE_OBJ_DIR_X86)/ $(RELEASE_OBJ_DIR_X64)/

# Phony Targets To Avoid Conflicts With File Names
.PHONY: all clean test release