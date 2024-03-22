

#include <iostream>


namespace Constants
{
    constexpr int MAX_NAME = 20;
    constexpr int MAX_AMOUNT_OF_EVENTS = 20;
}

using namespace Constants;

class Events
{
private:
    Event events[MAX_AMOUNT_OF_EVENTS];
public:
    Events(const Events* events, const int &numOfEv)
    {

    }
};


struct Date
{
    short day;
    short month;
    short year;
};


void copyDate(Date& destination, const Date& source)
{
    destination.day = source.day;
    destination.month = source.month;
    destination.year = source.year;
}

struct Time
{
    short hours;
    short minutes;
};

void copyTime(Time& destination, const Time& source)
{
    destination.hours = source.hours;
    destination.minutes = source.minutes;
}

int main()
{
    std::cout << "Hello World!\n";
}