# Makefile for Library Management System

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executable
TARGET = library_system

# Source files
SOURCES = main.cpp Book.cpp Student.cpp Library.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = Book.h Student.h Library.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install dependencies (for Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install -y g++ make

# Install dependencies (for CentOS/RHEL/Fedora)
install-deps-rpm:
	sudo yum install -y gcc-c++ make

# Install dependencies (for macOS)
install-deps-mac:
	brew install gcc make

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build the library system"
	@echo "  clean        - Remove build files"
	@echo "  run          - Build and run the program"
	@echo "  install-deps - Install dependencies (Ubuntu/Debian)"
	@echo "  help         - Show this help message"

.PHONY: all clean run install-deps install-deps-rpm install-deps-mac help
