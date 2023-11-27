#ifndef ROM_H
#define ROM_H

#include "device/device.hpp"
#include <vector>
#include <cstdint>

class Rom : public Device {
private:
    std::vector<uint8_t> rom;

public:
    Rom(size_t size);
    virtual void write(uint64_t data, uint64_t address, uint8_t width) override;
    virtual uint64_t read(uint64_t address, uint8_t width) override;
};

#endif // ROM_H
