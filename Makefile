# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -g -I CPU -I device -I system -I system/memory

# Define the main target
TARGET = edusim

# Source files
SOURCES = edusim.cpp system/memory/memory.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# First rule is the one executed when no parameters are fed to the Makefile
all: $(TARGET)

# Rule for linking the final program
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule for building each object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for cleaning up
clean:
	rm -f $(OBJECTS) $(TARGET)

# Include the dependency files
-include $(SOURCES:.cpp=.d)

# Rule for generating a dependency file by using the C preprocessor
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM -MT '$(patsubst %.cpp,%.o,$<)' $< -MF $@
