# Makefile for a C++ project
# ---------------------------------
# Make is a build automation tool that automatically builds executable programs and libraries from source code by reading files called Makefiles.
# A Makefile is a configuration file that specifies how and when to compile and link the source code files of a program.

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
LDFLAGS = -Wl,--stack,335544320

# Set the build mode (debug or release)
MODE ?= DEBUG

.PHONY: all
all: build
# Check if MODE is set to either debug or release
check_mode:

	@echo Checking mode.
	@echo MODE is set to $(MODE).
ifeq ($(filter $(MODE),DEBUG RELEASE),)
	$(error MODE must be set to either debug or release)
else
# Null operation prevents message "Nothing to be done" when MODE is set proprerly
	@: 
endif

ifeq ($(OS), Windows_NT)
    # Windows (CMD) doesn't like -p and uses backslashes
    MKDIR = if not exist $(subst /,\,$(1)) mkdir $(subst /,\,$(1))
    RM = del /Q
    RMDIR = rmdir /S /Q $(subst /,\,$(1))
    EXE = .exe
else
    # Linux/Unix
    MKDIR = mkdir -p $(1)
    RM = rm -f
    RMDIR = rm -rf $(1)
    EXE =
endif

# Adjust compiler flags based on the build mode
ifeq ($(MODE),release)
    CXXFLAGS += -O3  # Optimization for release mode
else
    CXXFLAGS += -g -Wall  # Debug symbols and warnings for debug mode
endif

# Directories and paths
BUILD_DIR = target
SRC_DIR = source
INCLUDE_DIR = include
TARGET_DIR = $(BUILD_DIR)/$(MODE)
OBJ_DIR = $(TARGET_DIR)/obj
TARGET = $(TARGET_DIR)/main$(EXE)

# List all source files in the src directory
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Generate a list of object files in the obj directory
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Default target builds the executable
#building the executable depends on the object files, which in turn depend on the source files
build: check_mode $(TARGET)

	@echo Building...
	@echo Compiling...
# Rule to compile .cpp to .o
# in $(sth) you have the variables$@ for the target, $< for the first prerequisite, and $^ for all prerequisites
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(call MKDIR, $(@D))
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -D $(MODE) -c $< -o $@

	@echo Linking...
# Rule to link object files into the final executable
$(TARGET): $(OBJ_FILES)
	@$(call MKDIR, $(@D))
	$(CXX) $(CXXFLAGS) $^ -o $@

	@echo Build complete: $(TARGET).
# Compile and Run
#builds runs the executable
run: build $(TARGET)
	@echo Running...
	./$(TARGET)

run_bst: build $(TARGET)
	@echo Running...
	./$(TARGET) --tree BST

analyze: run $(TARGET)
	@echo Creating charts...
	python .\charts\createGraphs.py
    # komendy, aby odpalić tę analizę wykresów.

# Clean target removes all generated files
clean:
	@echo Cleaning...
	$(RMDIR) $(BUILD_DIR)
	@echo Clean complete.


# Remove generated files and rebuild the project
rebuild: clean build
