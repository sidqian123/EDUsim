#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <cstdint>
#include <stdexcept>

class Memory {
private:
    std::vector<uint8_t> ram;
    std::vector<uint8_t> rom;
    const size_t MAX_ROM;
    const size_t MAX_RAM;

public:
    Memory(size_t ramSize, size_t romSize, size_t maxRam, size_t maxRom);

    // Read functions for different bit lengths
    uint8_t read8(size_t address) const;
    uint16_t read16(size_t address) const;
    uint32_t read32(size_t address) const;
    uint64_t read64(size_t address) const;

    // Write functions for different bit lengths
    void write8(size_t address, uint8_t value);
    void write16(size_t address, uint16_t value);
    void write32(size_t address, uint32_t value);
    void write64(size_t address, uint64_t value);

    //disassembly function
    unsigned int readDisassembler16(unsigned int address) const;
    unsigned int readDisassembler32(unsigned int address) const;
};

#endif // MEMORY_H
