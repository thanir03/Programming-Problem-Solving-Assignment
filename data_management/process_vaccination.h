#ifndef PROCESS_VACCINATION_H
#define PROCESS_VACCINATION_H
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "../type.h"
using namespace std;

vacc_appoinment_data process_vac_appoinment_data(string line);
vector<vacc_appoinment_data> read_vaccination_data(void);
bool write_vaccination_data(vector<vacc_appoinment_data> vac_app_list);
bool add_vaccination_data(vacc_appoinment_data vac_app);

#endif // PROCESS_VACCINATION_H