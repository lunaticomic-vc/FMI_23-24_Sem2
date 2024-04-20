//TODO: remove min, max, fix constants, add binaryprint

#include <iostream>
#include <fstream>
#include <algorithm>

class Multiset {
    static const int BITS_IN_BYTE = 8;

    unsigned char* set;
    unsigned int n;
    unsigned int k;
    unsigned int arraySize;

    int getByteIndex(unsigned int num) const {
        return (num * k) / BITS_IN_BYTE;
    }

    int getBitOffset(unsigned int num) const 
    {
        return (num * k) % BITS_IN_BYTE;
    }

    unsigned char getOccurrence(unsigned int num) const 
    {
        if (num < 1 || num > n) 
        {
            throw std::out_of_range("Number out of range");
        }

        int byteIndex = getByteIndex(num);
        int bitOffset = getBitOffset(num);

        unsigned int bitsNeeded = k;
        unsigned int result = 0;

        while (bitsNeeded > 0) 
        {
            unsigned int bitsInThisByte = std::min((unsigned int)(BITS_IN_BYTE - bitOffset), bitsNeeded);
            unsigned int mask = (1 << bitsInThisByte) - 1;
            unsigned int bits = (set[byteIndex] >> bitOffset) & mask;
            result |= (bits << (k - bitsNeeded));
            bitsNeeded -= bitsInThisByte;
            bitOffset = 0;
            byteIndex++;
        }

        return result;
    }

    void setOccurrence(unsigned int num, unsigned int count) 
    {
        if (num < 1 or num > n) 
        {
            throw std::out_of_range("Number out of range");
        }

        int byteIndex = getByteIndex(num);
        int bitOffset = getBitOffset(num);
        unsigned int bitsNeeded = k;

        while (bitsNeeded > 0) 
        {
            unsigned int bitsInThisByte = std::min((unsigned int)(BITS_IN_BYTE - bitOffset), bitsNeeded);
            unsigned int mask = (1 << bitsInThisByte) - 1;
            set[byteIndex] &= ~(mask << bitOffset);
            set[byteIndex] |= ((count >> (k - bitsNeeded)) & mask) << bitOffset;
            bitsNeeded -= bitsInThisByte;
            bitOffset = 0;
            byteIndex++;
        }
    }

public:
    Multiset(unsigned int n, unsigned int k) : n(n), k(k) 
    {
        if (k < 1 || k > 8) {
            throw std::invalid_argument("k must be between 1 and 8");
        }
        arraySize = ((n * k) + BITS_IN_BYTE) / BITS_IN_BYTE;
        set = new unsigned char[arraySize]();
    }

    ~Multiset() {
        delete[] set;
    }

    void addNumber(unsigned int num) 
    {
        unsigned int current = getOccurrence(num);

        if (current < ((1 << k) - 1)) 
        {
            setOccurrence(num, current + 1);
        }
        else 
        {
            throw std::overflow_error("Maximum occurrences reached");
        }
    }

    unsigned char howManyOcc(unsigned int num) const 
    {
        return getOccurrence(num);
    }

    void serializeToBin(const std::string& fileName) const 
    {
        std::ofstream file(fileName, std::ios::binary);

        file.write((char*)&n, sizeof(n));
        file.write((char*)&k, sizeof(k));
        file.write((char*)set, arraySize);
    }

    void deserializeFromBin(const std::string& fileName) 
    {
        std::ifstream file(fileName, std::ios::binary);

        file.read((char*)&n, sizeof(n));
        file.read((char*)&k, sizeof(k));

        delete[] set;

        arraySize = ((n * k) + BITS_IN_BYTE) / BITS_IN_BYTE;
        set = new unsigned char[arraySize]();
        file.read((char*)set, arraySize);
    }

    void printMultiset() const 
    {
        for (unsigned int i = 1; i <= n; ++i) {
            std::cout << i << ": " << (int)(howManyOcc(i)) << std::endl;
        }
    }
};

int main() {
    try {
        Multiset ms(10, 4);
        ms.addNumber(1);
        ms.addNumber(1);
        ms.addNumber(1);
        ms.addNumber(1);
        ms.addNumber(1);
        ms.addNumber(3);
        ms.addNumber(3);
        ms.addNumber(3);
        ms.addNumber(3);
        ms.addNumber(3);
        ms.printMultiset();
        ms.serializeToBin("multiset.bin");
        std::cout << std::endl;
        Multiset ms2(10, 4);
        ms2.deserializeFromBin("multiset.bin");
        ms2.printMultiset();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
