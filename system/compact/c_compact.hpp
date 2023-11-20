#ifdef __cplusplus
extern "C" {
#endif

//unsigned char serial_IO_read(unsigned int address);
//void serial_IO_write(unsigned int address, unsigned char data);
//int serial_IO_check(unsigned int address);
//unsigned int obio_pio_port(unsigned int address);
//void obio_pio_port_write(unsigned int address, unsigned int value);
//int obio_pio_port_check(unsigned int address);
//void databus_recorder(const char *string, unsigned int address, unsigned int size);
unsigned int m68k_read_disassembler_16(unsigned int address);
unsigned int m68k_read_disassembler_32(unsigned int address);
unsigned int  m68k_read_memory_8(unsigned int address);
unsigned int  m68k_read_memory_16(unsigned int address);
unsigned int  m68k_read_memory_32(unsigned int address);
void m68k_write_memory_8(unsigned int address, unsigned int value);
void m68k_write_memory_16(unsigned int address, unsigned int value);
void m68k_write_memory_32(unsigned int address, unsigned int value);

#ifdef __cplusplus
}
#endif