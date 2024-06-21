# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -g -Wall -Wextra -std=c++17

# Define the target executable
TARGET = search

# Define the source files
SRCS = src/search.cpp src/skiplist.cpp

# Define the object files (replace .cpp with .o in SRCS)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to avoid conflicts with files of the same name
.PHONY: all clean