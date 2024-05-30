#pragma once
#include <cstdint>

struct CriterionData 
{
    int32_t N;
    int32_t* args;
    int32_t* res;
};

bool criterionFuncType0(int32_t x, int32_t& result, void* data) 
{
    CriterionData* cdata = (CriterionData*)data;

    for (int i = 0; i < cdata->N; ++i) 
    {
        if (cdata->args[i] == x) 
        {
            result = cdata->res[i];
            return true;
        }
    }
    return false;
}

bool criterionFuncType1(int32_t x, int32_t& result, void* data) 
{
    CriterionData* cdata = (CriterionData*)data;

    for (int i = 0; i < cdata->N; ++i) 
    {
        if (cdata->args[i] == x) 
        {
            return false;
        }
    }
    result = x;

    return true;
}

bool criterionFuncType2(int32_t x, int32_t& result, void* data) 
{
    CriterionData* cdata = (CriterionData*)data;

    for (int i = 0; i < cdata->N; ++i) 
    {
        if (cdata->args[i] == x) 
        {
            result = 1;
            return true;
        }
    }
    result = 0;

    return true;
}

