#ifndef M68K_DEVICE_H
#define M68K_DEVICE_H

#include "device/device.hpp"
#define BUF_STEP_SIZE 100

class m68k_device : public Device {
public:
    m68k_device();
    virtual ~m68k_device();

    // Override the Device class's virtual methods
    virtual void write(unsigned int data,unsigned int address) override;
    //todo: will need to update this accordingly based on the implementation of ports
    //might need to change the return type to char* or string
    virtual unsigned int read(unsigned int address) override;

    // Additional methods specific to m68k_device can be added here
    void append_to_string(char **dest, const char *src, size_t *dest_size);
    unsigned char serial_IO_read(unsigned int address);
    void serial_IO_write(unsigned int address, unsigned char data);
    int serial_IO_check(unsigned int address);
    
    unsigned int obio_pio_port(unsigned int address);
    void obio_pio_port_write(unsigned int address, unsigned int value);
    int obio_pio_port_check(unsigned int address);

    
private:
    char *port_A_data, *port_B_data, *port_A_command, *port_B_command;
    size_t port_A_data_n, port_A_data_p;
    size_t port_B_data_n, port_B_data_p;
    size_t port_A_data_size, port_A_command_size, port_B_data_size, port_B_command_size;

    /* PIOs */
    unsigned int OBIO_PIO0A;	/* PIO-0 port A */
    unsigned int OBIO_PIO0B;	/* PIO-0 port B */
    unsigned int OBIO_PIO0C;    /* PIO-0 port C*/
    unsigned int OBIO_PIO0;	/* PIO-0 control */
    void exit_error(const char *format, ...);
};

#endif // M68K_DEVICE_H