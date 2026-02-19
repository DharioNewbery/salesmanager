#ifndef HELPER_HPP
#define HELPER_CPP

#include <string>
#include <stdexcept>

bool getDMY(const std::string& date, int& day, int& month, int& year) {
    std::string s_day, s_month, s_year;
    s_day = date.substr(0, 2);
    s_month = date.substr(2, 2);
    s_year = date.substr(4, 2);

    try
    {
        day = std::stoi(s_day);
        month = std::stoi(s_month);
        year = std::stoi(s_year);
    }
    catch(...) { return false; }

    return true;
}

bool isDateValid(const std::string& date)
{
    int day, month, year;
    if (!getDMY(date, day, month, year)) return false;
    
    if ((0 > day || day > 31)
    || (0 > month || month > 12)
    || (1000 > year || year > 9999)
    ) return false;
    
    return true;
}

unsigned long dateToMillis(const std::string& date)
{
    if (!isDateValid(date)) throw std::invalid_argument("The given string is not a valid date");

    int day, month, week;
}

std::string millisToDate(unsigned long dateMillis)
{
    return std::string();
}


#endif