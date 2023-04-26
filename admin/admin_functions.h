#ifndef ADMIN_FUNCTIONS_H
#define ADMIN_FUNCTIONS_H
#include <iostream>
#include <vector>
#include "../type.h"
using namespace std;

// Function Prototype

vector<user_data_struct> get_covid_19_positive(vector<user_data_struct> user_list);
void view_covid19_stats(void);
void view_covid19_positive(void);
vector<covid_19_stats> get_positive_stats(vector<user_data_struct> user_list);
vector<covid_19_stats> get_unvac_stats(vector<user_data_struct> user_list);
void view_vaccination_center(void);
void view_vaccination_appoinment(void);

#endif // ADMIN_FUNCTIONS_H