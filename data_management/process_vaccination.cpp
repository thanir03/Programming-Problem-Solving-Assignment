#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "../type.h"
#define splitter '|'
#define vaccination_data_file "data/vaccination.txt"
using namespace std;

// Function prototype

vacc_appoinment_data process_vac_appoinment_data(string line);
vector<vacc_appoinment_data> read_vaccination_data(void);
bool write_vaccination_data(vector<vacc_appoinment_data> vac_app_list);
bool add_vaccination_data(vacc_appoinment_data vac_app);

// convert line to struct type
vacc_appoinment_data process_vac_appoinment_data(string line)
{
    int i = 0;
    string data;
    vector<string> data_list = {};
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '|')
        {
            data_list.push_back(data);
            data = "";
            continue;
        }
        data += line[i];
    }
    data_list.push_back(data);
    vacc_appoinment_data vac_app_list = {
        username : data_list[0],
        vac_center : data_list[1],
        vac_date : data_list[2],
    };
    return vac_app_list;
}

// read vaccination data
vector<vacc_appoinment_data> read_vaccination_data(void)
{
    fstream vac_db;
    vac_db.open(vaccination_data_file, ios::in);
    if (!vac_db.is_open())
    {
        cout << "Unable to read data";
    }
    string line;
    vector<vacc_appoinment_data> vacc_app_list;
    while (!vac_db.eof())
    {
        getline(vac_db, line);
        if (line == "")
        {
            break;
        }
        vacc_app_list.push_back(process_vac_appoinment_data(line));
    }
    vac_db.close();
    return vacc_app_list;
}

// rewrite the entire vaccination.txt file
bool write_vaccination_data(vector<vacc_appoinment_data> vac_app_list)
{
    fstream vac_db;
    vac_db.open(vaccination_data_file, ios::out);
    if (!vac_db.is_open())
    {
        cout << "Unable to read data";
        return false;
    }
    for (int i = 0; i < vac_app_list.size(); i++)
    {
        vac_db << vac_app_list[i].username << splitter << vac_app_list[i].vac_center << splitter << vac_app_list[i].vac_date << "\n";
    }
    vac_db.close();
    return true;
}

// append new vaccination data to the end of the file
bool add_vaccination_data(vacc_appoinment_data vac_app)
{
    fstream vac_db;
    vac_db.open(vaccination_data_file, ios::app);
    if (!vac_db.is_open())
    {
        cout << "Unable to read data";
        return false;
    }
    vac_db << vac_app.username << splitter << vac_app.vac_center << splitter << vac_app.vac_date << "\n";
    vac_db.close();
    return true;
}
