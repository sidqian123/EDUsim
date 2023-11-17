#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
public:
    // Virtual methods for devices
    virtual ~Device() {}
    virtual void write(const std::string& data) = 0;
    virtual std::string read() = 0;
};

#endif // DEVICE_H
