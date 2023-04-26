#ifndef USER_FUNCTIONS_H
#define USER_FUNCTIONS_H
#include <iostream>
#include <string>
#include <vector>
#include "../type.h"

void view_user_profile(user_data_struct user);
void update_profile(user_data_struct user);
vector<string> get_action_list(string username);
void update_covid19_symptoms(user_data_struct user);
bool validate_test_date(string date);

#endif // USER_FUNCTIONS_H
