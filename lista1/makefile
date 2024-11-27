# Compiler
CC = g++

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRC_FILES = $(SRC_DIR)/FA.c $(SRC_DIR)/KMP.c

# Executable names (based on source file names)
EXEC_FA = $(BUILD_DIR)/FA.exe
EXEC_KMP = $(BUILD_DIR)/KMP.exe

# Compilation flags
CFLAGS = -Wall -Wextra -std=c++11

# Default target: builds both executables
all: $(EXEC_FA) $(EXEC_KMP)

# Compile FA.c to build/FA.exe
$(EXEC_FA): $(SRC_DIR)/FA.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(EXEC_FA) $(SRC_DIR)/FA.c

# Compile KMP.c to build/KMP.exe
$(EXEC_KMP): $(SRC_DIR)/KMP.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(EXEC_KMP) $(SRC_DIR)/KMP.c

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run the FA executable with arguments
run_FA: $(EXEC_FA)
	@echo "Running FA..."
	@$(EXEC_FA) $(pattern) $(filename)

# Run the KMP executable with arguments
run_KMP: $(EXEC_KMP)
	@echo "Running KMP..."
	@$(EXEC_KMP) $(pattern) $(filename)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run_FA run_KMP clean
