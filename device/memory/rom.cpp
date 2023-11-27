#include "rom.hpp"
#include <stdexcept>

Rom::Rom(size_t size) {
    rom.resize(size);
}

void Rom::write(uint64_t data, uint64_t address, uint8_t width) {
    throw std::runtime_error("Write operation not supported on ROM");
}

uint64_t Rom::read(uint64_t address, uint8_t width) {
    if (address + width > rom.size()) {
        throw std::out_of_range("Read address out of range");
    }

    uint64_t value = 0;
    for (size_t i = 0; i < width; ++i) {
        value |= static_cast<uint64_t>(rom[address + i]) << (8 * i);
    }
    return value;
}
