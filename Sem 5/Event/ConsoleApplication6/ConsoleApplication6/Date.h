#pragma once


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
