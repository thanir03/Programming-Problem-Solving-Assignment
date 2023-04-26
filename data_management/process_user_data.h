#ifndef PROCESS_USER_DATA_H
#define PROCESS_USER_DATA_H
#include <string>
#include <vector>
#include "../type.h"
using namespace std;

user_data_struct process_single_user_data(string line);
vector<user_data_struct> read_user_data(void);
void write_user_data(vector<user_data_struct> user_data);
bool add_user_data(user_data_struct new_user);

#endif // PROCESS_USER_DATA_H