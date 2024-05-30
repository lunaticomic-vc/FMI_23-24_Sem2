#include <iostream>
#include <fstream>
#include <stdexcept>

#include "PartialFunction.h"
#include "CriterionPartialFunction.h"
#include "MaxPartialFunction.h"
#include "MinPartialFunction.h"
#include "helper_functions.h"

PartialFunction* createFunctionFromFile(const char* filename)
{
    std::ifstream file(filename, std::ios::binary);

    if (!file) 
    {
        throw std::runtime_error("Error opening file");
    }

    uint16_t N, T;

    file.read((char*)&N, sizeof(uint16_t));
    file.read((char*)&T, sizeof(uint16_t));

    CriterionData* data = new CriterionData;

    data->N = N;
    data->args = new int32_t[N];
    data->res = new int32_t[N];

    for (int i = 0; i < N; ++i)
    {
        data->args[i] = i;
        data->res[i] = i;
    }
    file.close();

    return new CriterionPartialFunction(criterionFuncType0, data);
}

int main()
{
    std::ifstream inputFile("func.dat", std::ios::binary);

    if (!inputFile)
    {
        std::cout << "Error opening file func.dat" << std::endl;
        return 1;
    }

    uint16_t N, T;
    inputFile.read((char*)&N, sizeof(N));
    inputFile.read((char*)&T, sizeof(T));

    PartialFunction* func = nullptr;

    if (T == 0) 
    {
        CriterionData* data = new CriterionData;

        data->N = N;
        data->args = new int32_t[N];
        data->res = new int32_t[N];

        inputFile.read((char*)data->args, N * sizeof(int32_t));
        inputFile.read((char*)data->res, N * sizeof(int32_t));

        func = new CriterionPartialFunction(criterionFuncType0, data);
    }
    else if (T == 1) 
    {
        CriterionData* data = new CriterionData;

        data->N = N;
        data->args = new int32_t[N];
        data->res = nullptr;
        
        inputFile.read((char*)data->args, N * sizeof(int32_t));

        func = new CriterionPartialFunction(criterionFuncType1, data);
    }
    else if (T == 2) 
    {
        CriterionData* data = new CriterionData;

        data->N = N;
        data->args = new int32_t[N];
        data->res = nullptr;

        inputFile.read((char*)data->args, N * sizeof(int32_t));

        func = new CriterionPartialFunction(criterionFuncType2, data);
    }
    else if (T == 3 || T == 4) 
    {
        char** filenames = new char* [N];

        for (int i = 0; i < N; ++i) 
        {
            filenames[i] = new char[256];
            inputFile.read(filenames[i], 256);
        }

        PartialFunction** partialFunctions = new PartialFunction * [N];

        for (int i = 0; i < N; ++i) 
        {
            partialFunctions[i] = createFunctionFromFile(filenames[i]);
            delete[] filenames[i];
        }
        delete[] filenames;

        if (T == 3) 
        {
            func = new MaxPartialFunction(partialFunctions, N);
        }
        else 
        {
            func = new MinPartialFunction(partialFunctions, N);
        }
    }
    else 
    {
        std::cout << "Unknown function type " << T << std::endl;
        return 1;
    }

    inputFile.close();

    int a, b;
    std::cin >> a >> b;

    for (int i = a; i <= b; ++i) 
    {
        if (func->isDefinedAt(i)) 
        {
            std::cout << "f(" << i << ") = " << func->compute(i) << "   ";
        }
    }
    std::cout << std::endl;

    delete func;

    return 0;
}
