#ifndef PROCESS_VACCINATI0N_CENTER_H
#define PROCESS_VACCINATION_CENTER_H
#include <vector>
#include <string>
#include "../type.h"
using namespace std;

vac_center_data process_vac_centre_data(string single_line);
vector<vac_center_data> read_vacc_center_data(void);

#endif // PROCESS_VACCINATION_CENTER_H