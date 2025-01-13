# Compiler and Flags
CXX = g++
CXX_MAIN_FLAGS = -Iinclude/ -O3 -Wall -Wextra -std=c++17 -DMAIN
CXX_TEST_FLAGS = -Iinclude/ -O3 -Wall -Wextra -std=c++17 -DTEST_060120250539_ENCRYPTDECRYPT

# Directories
SRC_DIR = src
TEST_DIR = test/06-01-2025-05-39
OBJ_DIR = build/linux

TEST_OBJ_DIR_X86 = $(OBJ_DIR)/test/x86
TEST_OBJ_DIR_X64 = $(OBJ_DIR)/test/x64

RELEASE_OBJ_DIR_X86 = $(OBJ_DIR)/release/x86
RELEASE_OBJ_DIR_X64 = $(OBJ_DIR)/release/x64

# Source Files
MAIN_SRC = \
	$(SRC_DIR)/Exception/Exception.cpp \
	$(SRC_DIR)/Crypt/Caesar/Caesar.cpp \
	$(SRC_DIR)/Crypt/Caesar/SCaesar/SCaesar.cpp \
	$(SRC_DIR)/Crypt/Bitwise/Bitwise.cpp \
	$(SRC_DIR)/FileStream/CFile/CFile.cpp \
	$(SRC_DIR)/Main/Main.cpp

TEST_SRC = \
	$(SRC_DIR)/Exception/Exception.cpp \
	$(SRC_DIR)/Crypt/Caesar/Caesar.cpp \
	$(SRC_DIR)/Crypt/Caesar/SCaesar/SCaesar.cpp \
	$(SRC_DIR)/Crypt/Bitwise/Bitwise.cpp \
	$(SRC_DIR)/FileStream/CFile/CFile.cpp \
	$(SRC_DIR)/Test/Test.cpp \
	$(TEST_DIR)/EncryptDecryptTest.cpp
	
# Object Files
TEST_OBJ_X86 = $(TEST_SRC:%.cpp=$(TEST_OBJ_DIR_X86)/%.o)
TEST_OBJ_X64 = $(TEST_SRC:%.cpp=$(TEST_OBJ_DIR_X64)/%.o)

RELEASE_OBJ_X86 = $(MAIN_SRC:%.cpp=$(RELEASE_OBJ_DIR_X86)/%.o)
RELEASE_OBJ_X64 = $(MAIN_SRC:%.cpp=$(RELEASE_OBJ_DIR_X64)/%.o)

# Target Executables
TEST_TARGET_X86 = $(TEST_OBJ_DIR_X86)/LinsomwareTest86
TEST_TARGET_X64 = $(TEST_OBJ_DIR_X64)/LinsomwareTest64

RELEASE_TARGET_X86 = $(RELEASE_OBJ_DIR_X86)/Linsomware
RELEASE_TARGET_X64 = $(RELEASE_OBJ_DIR_X64)/Linsomware

# Default Target
all: release

# Test Target
test: $(TEST_TARGET_X86) $(TEST_TARGET_X64)

$(TEST_TARGET_X86): $(TEST_OBJ_X86)
	@mkdir -p $(dir $@)
	$(CXX) -m32 $(CXX_TEST_FLAGS) $(TEST_OBJ_X86) -o $@

$(TEST_TARGET_X64): $(TEST_OBJ_X64)
	@mkdir -p $(dir $@)
	$(CXX) -m64 $(CXX_TEST_FLAGS) $(TEST_OBJ_X64) -o $@

$(TEST_OBJ_DIR_X86)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_TEST_FLAGS) -m32 -c $< -o $@

$(TEST_OBJ_DIR_X64)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_TEST_FLAGS) -m64 -c $< -o $@

# Release Targets
release: $(RELEASE_TARGET_X86) $(RELEASE_TARGET_X64)

$(RELEASE_TARGET_X86): $(RELEASE_OBJ_X86)
	@mkdir -p $(dir $@)
	$(CXX) -m32 $(RELEASE_OBJ_X86) -o $@

$(RELEASE_TARGET_X64): $(RELEASE_OBJ_X64)
	@mkdir -p $(dir $@)
	$(CXX) -m64 $(RELEASE_OBJ_X64) -o $@

$(RELEASE_OBJ_DIR_X86)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_MAIN_FLAGS) -m32 -c $< -o $@

$(RELEASE_OBJ_DIR_X64)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_MAIN_FLAGS) -m64 -c $< -o $@

# Clean Target To Remove The Files
clean-test:
	rm -rf $(TEST_OBJ_DIR_X86)/ $(TEST_OBJ_DIR_X64)/

clean-release:
	rm -rf $(RELEASE_OBJ_DIR_X86)/ $(RELEASE_OBJ_DIR_X64)/

# Phony Targets To Avoid Conflicts With File Names
.PHONY: all clean test release