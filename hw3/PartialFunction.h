#pragma once
#include <cstdint>

class PartialFunction 
{
public:
    virtual ~PartialFunction() {}
    virtual bool isDefinedAt(int32_t x) const = 0;
    virtual int32_t compute(int32_t x) const = 0;
};

