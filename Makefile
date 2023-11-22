# Compiler settings
CC = gcc
CXX = g++
CFLAGS = -g -Wall -I.
CXXFLAGS = -g -Wall -I.
LDFLAGS =

# Source files
SOURCES = edusim.cpp \
          CPU/m68k/luna_cpu.cpp \
          device/m68k_device.cpp \
          compact/c_compat.cpp \
          system/memory/memory.cpp \
          system/soft/m68k_in.c \
          system/soft/m68kcpu.c \
          system/soft/m68kdasm.c \
          system/soft/m68kfpu.c \
          system/soft/m68kmake.c \
          system/soft/m68kops.c \
          system/soft/sim.c

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

# Build target
TARGET = edusim

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

# Compiling C++ sources
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compiling C sources
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJECTS)

# Dependencies
system/compact/c_compat.o: CPU/m68k/soft/compact device/memory
system/memory/memory.o: device/memory
device/m68k_device.o: device/obio/m68k_device.hpp
