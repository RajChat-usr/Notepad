# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = /usr/include
LIB_DIR = /usr/lib

# Source files and target executable
SRC = $(SRC_DIR)/TicTacToe.cpp
TARGET = $(BIN_DIR)/TicTacToe

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Clean up the compiled files
clean:
	rm -f $(TARGET)
