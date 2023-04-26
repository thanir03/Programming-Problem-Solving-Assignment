#ifndef USER_VACCINATION_H
#define USER_VACCINATION_H
#include <string>
#include <vector>
#include "../type.h"
using namespace std;

void filter_vac_appoinment();
void change_vaccination_status(vector<vacc_appoinment_data> completed_vac_app);
vacc_appoinment_data find_vac_app(string username);
string get_vacc_date(user_data_struct user);
void display_vaccination_app(vacc_appoinment_data user_app);

#endif // USER_VACCINATION_H