#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
public:
    // Virtual methods for devices
    virtual ~Device() {}
    virtual void write(uint64_t data,uint64_t address, uint8_t width) = 0;

    //todo: will need to update this accordingly based on the implementation of ports 
    //might need to change the return type to char* or string
    virtual uint64_t read(uint64_t address, uint8_t width) = 0;
};

#endif // DEVICE_H

