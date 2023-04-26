#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

// Function prototype

time_t parse_string_date(string date);
string parse_date_object(time_t date);

// convert date from string to time in seconds
time_t parse_string_date(string date)
{
    int day, month, year;
    sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
    struct tm date_struct = {};
    date_struct.tm_mday = day;
    date_struct.tm_mon = month - 1;
    date_struct.tm_year = year - 1900;
    time_t date_time = mktime(&date_struct);
    return date_time;
}

// convert time in seconds to formatted date strings
string parse_date_object(time_t date)
{
    tm *date_object = localtime(&date);
    return to_string(date_object->tm_mday) + "/" + to_string(date_object->tm_mon + 1) + "/" + to_string(date_object->tm_year + 1900);
}
