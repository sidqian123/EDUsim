# Compiler settings
CC = gcc
CXX = g++
CFLAGS = -g -Wall -I.
CXXFLAGS = -g -Wall -I.
LDFLAGS =

# Source files
SOURCES = edusim.cpp \
          CPU/m68k/soft/c_compat.cpp \
          CPU/m68k/soft/m68k_in.c \
          CPU/m68k/soft/m68kcpu.c \
          CPU/m68k/soft/m68kdasm.c \
          CPU/m68k/soft/m68kfpu.c \
          CPU/m68k/soft/m68kmake.c \
          CPU/m68k/soft/m68kops.c \
          CPU/m68k/soft/sim.c \
          device/memory/ram.cpp \
          device/memory/rom.cpp \
          device/obio/m68k_device.cpp

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
CPU/m68k/soft/c_compat.o: CPU/m68k/soft/compact/c_compact.hpp
device/memory/ram.o: device/memory/ram.hpp
device/memory/rom.o: device/memory/rom.hpp
device/obio/m68k_device.o: device/obio/m68k_device.hpp
