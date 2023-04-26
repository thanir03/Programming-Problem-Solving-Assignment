#include <iostream>
#include <fstream>
#include <vector>
#define splitter '|'
#include "../type.h"
#define vac_center_file "data/vaccination_center.txt"
using namespace std;

// Function prototype

vac_center_data process_vac_centre_data(string single_line);
vector<vac_center_data> read_vacc_center_data(void);

// convert line to struct type
vac_center_data process_vac_centre_data(string single_line)
{
    vector<string> data_list = {};
    string data;
    for (int i = 0; i < single_line.length(); i++)
    {
        if (single_line[i] == '|')
        {
            data_list.push_back(data);
            data = "";
            continue;
        }
        data += single_line[i];
    }
    data_list.push_back(data);
    vac_center_data vac_center = {
        state : stoi(data_list[0]),
        vac_center_name : data_list[1]
    };
    return vac_center;
}

// reading the vaccination_center.txt file
vector<vac_center_data> read_vacc_center_data(void)
{
    fstream vac_center_db;
    vac_center_db.open(vac_center_file, ios::in);
    if (!vac_center_db.is_open())
    {
        cout << "Failed to open the vaccination center database";
        return {};
    }
    vector<vac_center_data> list_of_vac_center = {};
    string single_line;
    while (!vac_center_db.eof())
    {
        getline(vac_center_db, single_line);
        if (single_line == "")
            break;
        list_of_vac_center.push_back(process_vac_centre_data(single_line));
    }
    return list_of_vac_center;
}