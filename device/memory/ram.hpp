#ifndef RAM_H
#define RAM_H

#include "device/device.hpp"
#include <vector>
#include <cstdint>

class Ram : public Device {
private:
    std::vector<uint8_t> ram;

public:
    Ram(size_t size);
    virtual void write(uint64_t data, uint64_t address, uint8_t width) override;
    virtual uint64_t read(uint64_t address, uint8_t width) override;
};

#endif // RAM_H
