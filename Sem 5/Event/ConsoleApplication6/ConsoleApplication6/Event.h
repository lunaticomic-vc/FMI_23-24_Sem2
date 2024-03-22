#pragma once
#include "Date.h"
#include "Time.h"

class Event
{
private:
    char name[MAX_NAME];
    Date date;
    Time begin;
    Time end;
public:
    Event();
    Event(const char* name, const Date& date, const Time& begin, const Time& end);

    void setName(const char* name)
    {
        strcpy(this->name, name);
    }

    void setDate(const Date& date)
    {
        copyDate(this->date, date);
    }

    void setBegin(const Time& begin)
    {
        copyTime(this->begin, begin);
    }

    void setEnd(const  Time& end)
    {
        copyTime(this->end, end);
    }

    char* getName(const char* name) const
    {
        return (char*)this->name;
    }

    Date getDate(const Date& date) const
    {
        return this->date;
    }

    Time getBegin(const Time& begin) const
    {
        return this->begin;
    }

    Time getBegin(const Time& end) const
    {
        return this->end;
    }
};

Event::Event() : name(), date(0,0,0), begin(), end();

Event::Event(const char* name, const Date& date, const Time& begin, const Time& end)
{
    setName(name);
    setDate(date);
    setBegin(begin);
    setEnd(end);
}