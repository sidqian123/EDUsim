#include "ram.hpp"
#include <stdexcept>

Ram::Ram(size_t size) {
    ram.resize(size);
}

void Ram::write(uint64_t data, uint64_t address, uint8_t width) {
    if (address + width > ram.size()) {
        throw std::out_of_range("Write address out of range");
    }

    for (size_t i = 0; i < width; ++i) {
        ram[address + i] = (data >> (8 * i)) & 0xFF;
    }
}

uint64_t Ram::read(uint64_t address, uint8_t width) {
    if (address + width > ram.size()) {
        throw std::out_of_range("Read address out of range");
    }

    uint64_t value = 0;
    for (size_t i = 0; i < width; ++i) {
        value |= static_cast<uint64_t>(ram[address + i]) << (8 * i);
    }
    return value;
}
