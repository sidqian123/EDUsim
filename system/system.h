#ifndef SYSTEM_H
#define SYSTEM_H

#include "CPU/cpu.h"
#include "device/device.h"

class System {
public:
    virtual ~System() {}
    virtual void init() = 0;
    virtual void loadConfiguration(const std::string& configPath) = 0;
    virtual void run() = 0;
};

#endif // SYSTEM_H
