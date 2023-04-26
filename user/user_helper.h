#ifndef USER_HELPER_H
#define USER_HELPER_H
#include <vector>
#include <string>
#include "../type.h"
using namespace std;

user_data_struct has_username_in_db(vector<user_data_struct> data, string username);
void change_single_user_data(user_data_struct user);

#endif // USER_HELPER_H