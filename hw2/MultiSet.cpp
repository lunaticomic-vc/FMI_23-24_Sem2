#include <iostream>
#include <fstream>

class MultiSet {
private:
    unsigned char* counts; // Times each number is included
    int maxNumber; // Biggest number
    int maxCount; // (2^k - 1)

public:
    MultiSet(int n, int k) {
        maxNumber = n;
        maxCount = (1 << k) - 1;
        counts = new unsigned char[n + 1]; // allocate memory for n+1 numbers
        std::fill(counts, counts + n + 1, 0); // fill array with zeroes
    }

    ~MultiSet() {
        delete[] counts;
    }

    void add(int number) 
    {
        if (number <= maxNumber && counts[number] < maxCount) 
        {
            counts[number]++;
        }
    }

    int count(int number) const 
    {
        if (number > maxNumber) return 0;
        return counts[number];
    }

    void print() const 
    {
        for (int i = 0; i <= maxNumber; ++i) 
        {
            if (counts[i] > 0) 
            {
                std::cout << i << " appears " << (int)counts[i] << " times\n";
            }
        }
    }

    void printRaw() const 
    {
        std::cout << "Memory representation:\n";
      
        for (int i = 0; i <= maxNumber; ++i) 
        {
            std::cout << (int)counts[i] << " ";
        }
        std::cout << "\n";
    }

    void serialize(const char* filename) const 
    {
        std::ofstream out(filename, std::ios::binary);
      
        if(out.is_open())
        {
          out.write((char*)counts, maxNumber + 1);
          out.close();
        }
        else 
            std::cout << "File issue"<< std::cout;
    }

    void deserialize(const char* filename) 
    {
        std::ifstream in(filename, std::ios::binary);

       if(out.is_open())
        {
          in.read((char*)counts, maxNumber + 1);
          in.close();
        }
        else 
            std::cout << "File issue"<< std::cout;
    }

    MultiSet intersection(const MultiSet& other) const 
    {
        MultiSet result(maxNumber, std::min((int)log2(maxCount + 1), (int)log2(other.maxCount + 1)));
      
        for (int i = 0; i <= maxNumber; ++i) 
        {
            result.counts[i] = std::min(counts[i], other.counts[i]);
        }
      
        return result;
    }

    MultiSet difference(const MultiSet& other) const 
{
        MultiSet result(maxNumber, std::min((int)log2(maxCount + 1), (int)log2(other.maxCount + 1)));
  
        for (int i = 0; i <= maxNumber; ++i) 
        {
            result.counts[i] = counts[i] > other.counts[i] ? counts[i] - other.counts[i] : 0;
        }
  
        return result;
    }

    MultiSet complement() const 
{
        MultiSet result(maxNumber, std::min((int)log2(maxCount + 1), (int)log2(maxCount + 1)));
  
        for (int i = 0; i <= maxNumber; ++i) 
        {
            result.counts[i] = maxCount - counts[i];
        }
        return result;
    }
};
