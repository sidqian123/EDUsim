#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
public:
    // Virtual methods for devices
    virtual ~Device() {}
    virtual void write(unsigned int data,unsigned int address) = 0;

    //todo: will need to update this accordingly based on the implementation of ports 
    //might need to change the return type to char* or string
    virtual unsigned int read(unsigned int address) = 0;
};

#endif // DEVICE_H

