#pragma once

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