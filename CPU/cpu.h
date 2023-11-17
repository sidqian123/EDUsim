#ifndef CPU_H
#define CPU_H

#include <string>

class CPU {
public:
    // Virtual methods for cpu
    virtual ~CPU() {}
    virtual void init() = 0;
    virtual void setCpuType(const std::string& type) = 0;
    virtual void pulseReset() = 0;
    virtual void execute() = 0;
};

#endif // CPU_H
