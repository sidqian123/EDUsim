#include "c_compact.hpp"
#include "system/memory/memory.hpp"

unsigned int  m68k_read_memory_8(unsigned int address){
    return Memory::read8(address);
}
unsigned int  m68k_read_memory_16(unsigned int address){
    return Memory::read16(address);
}
unsigned int  m68k_read_memory_32(unsigned int address){
    return Memory::read32(address);
}
void m68k_write_memory_8(unsigned int address, unsigned int value){
    Memory::write8(address, value);
}
void m68k_write_memory_16(unsigned int address, unsigned int value){
    Memory::write16(address, value);
}
void m68k_write_memory_32(unsigned int address, unsigned int value){
    Memory::write32(address, value);
}

unsigned int m68k_read_disassembler_16(unsigned int address){
    return Memory::readDisassembler16(address);
}

unsigned int m68k_read_disassembler_32(unsigned int address){
    return Memory::readDisassembler32(address);
}
void data_bus_recorder(const char *string, unsigned int address, unsigned int size);