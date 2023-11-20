#include "memory.hpp"
using namespace std;
#include <iostream>

// Constructor
Memory::Memory(size_t ramSize, size_t romSize){}

void Memory::initialize(size_t ramSize, size_t romSize) {
    ram.resize(ramSize);
    rom.resize(romSize);
}

// Template function for reading
template <typename T>
T readValue(const std::vector<uint8_t>& memory, size_t address) {
    if (address + sizeof(T) > memory.size()) {
        throw std::out_of_range("Read address out of range");
    }

    T value = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        value |= static_cast<T>(memory[address + i]) << (8 * i);
    }
    return value;
}

// Template function for writing
template <typename T>
void writeValue(std::vector<uint8_t>& memory, size_t address, T value) {
    if (address + sizeof(T) > memory.size()) {
        throw std::out_of_range("Write address out of range");
    }

    for (size_t i = 0; i < sizeof(T); ++i) {
        memory[address + i] = (value >> (8 * i)) & 0xFF;
    }
}

void exit_error(const char* error_msg, unsigned int address) {
    std::cerr << "Error: " << error_msg << address << std::endl;
    std::exit(EXIT_FAILURE);
}

unsigned int Memory::readDisassembler16(unsigned int address) {
    if (address > rom.size()) {
        exit_error("Disassembler attempted to read word from ROM address %08x\n", address);
    }
    return readValue<uint16_t>(rom, address);
}

unsigned int Memory::readDisassembler32(unsigned int address) {
    if (address > rom.size()) {
        exit_error("Disassembler attempted to read long from ROM address %08x\n", address);
    }
    return readValue<uint32_t>(rom, address);
}

// Read methods
uint8_t Memory::read8(size_t address) { return readValue<uint8_t>(ram, address); }
uint16_t Memory::read16(size_t address) { return readValue<uint16_t>(ram, address); }
uint32_t Memory::read32(size_t address) { return readValue<uint32_t>(ram, address); }
uint64_t Memory::read64(size_t address) { return readValue<uint64_t>(ram, address); }

// Write methods
void Memory::write8(size_t address, uint8_t value) { writeValue<uint8_t>(ram, address, value); }
void Memory::write16(size_t address, uint16_t value) { writeValue<uint16_t>(ram, address, value); }
void Memory::write32(size_t address, uint32_t value) { writeValue<uint32_t>(ram, address, value); }
void Memory::write64(size_t address, uint64_t value) { writeValue<uint64_t>(ram, address, value); }
