#pragma once
#include "PartialFunction.h"
#include "helper_functions.h"

typedef bool (*CriterionFunc)(int32_t, int32_t&, void*);

class CriterionPartialFunction : public PartialFunction 
{
    CriterionFunc func;
    void* data;

public:
    CriterionPartialFunction(CriterionFunc f, void* d) : func(f), data(d) {}

    bool isDefinedAt(int32_t x) const override 
    {
        int32_t dummy;
        return func(x, dummy, data);
    }

    int32_t compute(int32_t x) const override 
    {
        int32_t result;
        func(x, result, data);
        return result;
    }

    ~CriterionPartialFunction() 
    {
        delete[]((CriterionData*)data)->args;
        delete[]((CriterionData*)data)->res;
        delete (CriterionData*)data;
    }
};
