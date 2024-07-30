# Compiler
# CXX = clang++
CXX = g++

# Compiler Flags
# CXXFLAGS = -fcolor-diagnostics -fansi-escape-codes -g
CXXFLAGS = -std=c++20 -Wall

# Include and Library Directories
INCLUDES = -I/opt/homebrew/Cellar/sfml/2.6.1/include -I./View -I./Model -I./Controller
LIBDIRS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib

# SFML Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source Files
SRCS = $(wildcard *.cpp)

# Object Files
OBJS = $(SRCS:.cpp=.o)

# Executable Name
EXEC = $(basename $(SRCS))

# Default target
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBDIRS) $(LIBS)

# Rule to create object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean

