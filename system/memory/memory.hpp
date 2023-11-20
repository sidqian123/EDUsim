#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <cstdint>
#include <stdexcept>

class Memory {
public:
    Memory(size_t ramSize, size_t romSize);

    static std::vector<uint8_t> ram;
    static std::vector<uint8_t> rom;

    static void initialize(size_t ramSize, size_t romSize);

    // Read functions for different bit lengths
    static uint8_t read8(size_t address);
    static uint16_t read16(size_t address);
    static uint32_t read32(size_t address);
    static uint64_t read64(size_t address);

    // Write functions for different bit lengths
    static void write8(size_t address, uint8_t value);
    static void write16(size_t address, uint16_t value);
    static void write32(size_t address, uint32_t value);
    static void write64(size_t address, uint64_t value);

    //disassembly function
    static unsigned int readDisassembler16(unsigned int address);
    static unsigned int readDisassembler32(unsigned int address);
};

#endif // MEMORY_H
