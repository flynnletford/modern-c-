# Compiler
CXX := clang++  # Change to g++ if using GCC

# Compiler flags
CXXFLAGS := -std=c++20 -g -Wall -Wextra -Wpedantic -fcolor-diagnostics -fansi-escape-codes -O2

# Target executable
TARGET := main

# Source files
SRC := $(wildcard *.cpp)

# Object files
OBJ := $(SRC:.cpp=.o)

# Default build target
all: $(TARGET) postbuild

# Link object files into the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove object files after build
postbuild:
	rm -f $(OBJ)

# Clean build files
.PHONY: clean postbuild
clean:
	rm -f $(OBJ) $(TARGET)
