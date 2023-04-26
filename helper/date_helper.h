#ifndef DATE_HELPER_H
#define DATE_HELPER_H
#include <string>
#include <ctime>
using namespace std;

time_t parse_string_date(string date);
string parse_date_object(time_t date);

#endif // DATE_HELPER_H