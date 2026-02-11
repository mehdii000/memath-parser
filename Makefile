# Compiler and Flags
CXX      = g++-14
CXXFLAGS = -Wall -Wextra -std=c++23 -Iincludes
TARGET   = memath

# Directories
SRC_DIR  = src
SRCS     = $(wildcard $(SRC_DIR)/*.cpp)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean up
clean:
	rm -f $(TARGET)

# Run the program
run: all
	./$(TARGET)
