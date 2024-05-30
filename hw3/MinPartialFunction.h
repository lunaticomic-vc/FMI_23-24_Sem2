#pragma once
#include "PartialFunction.h"

class MinPartialFunction : public PartialFunction 
{
    PartialFunction** functions;
    int functionCount;

public:
    MinPartialFunction(PartialFunction** funcs, int count) : functions(funcs), functionCount(count) {}

    bool isDefinedAt(int32_t x) const override 
    {
        for (int i = 0; i < functionCount; ++i) 
        {
            if (!functions[i]->isDefinedAt(x)) return false;
        }
        return true;
    }

    int32_t compute(int32_t x) const override 
    {
        int32_t minVal = functions[0]->compute(x);

        for (int i = 1; i < functionCount; ++i) 
        {
            int32_t val = functions[i]->compute(x);
            if (val < minVal) minVal = val;
        }
        return minVal;
    }

    ~MinPartialFunction() 
    {
        for (int i = 0; i < functionCount; ++i) 
        {
            delete functions[i];
        }
        delete[] functions;
    }
};