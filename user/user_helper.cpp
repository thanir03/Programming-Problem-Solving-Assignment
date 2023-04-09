#pragma once
#include "../data_management/process_user_data.cpp"
using namespace std;

user_data_struct has_username_in_db(vector<user_data_struct> data, string username);

vector<string> covid_19_status = {
    "Confirmed Case",
    "Suspected Case",
    "High Risk",
    "Low Risk",
};
vector<string> state_list = {
    "Johor",
    "Kedah",
    "Kelantan",
    "Melaka",
    "Negeri Sembilan",
    "Pahang",
    "Penang",
    "Perak",
    "Perlis",
    "Selangor",
    "Terengganu",
    "Sabah",
    "Sarawak",
    "Kuala Lumpur",
};

vector<string> list_of_actions = {
    "PERFORM A COVID-19 TEST", "UPDATE YOUR TEST RESULT IN MEDICAL HISTORY MENU", "QUARANTINE FOR 3 DAYS", "QUARANTINE FOR 10 DAYS", "APPLY FOR VACCINATION"};

user_data_struct has_username_in_db(vector<user_data_struct> data, string username)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].username == username)
        {
            return data[i];
        }
    }
    return {};
}

void change_single_user_data(user_data_struct user)
{
    vector<user_data_struct> user_list = read_user_data();
    for (int i = 0; i < user_list.size(); i++)
    {
        if (user_list[i].username == user.username)
        {
            user_list[i] = user;
        }
    }
    write_user_data(user_list);
}

//  username|password|phone_num|ic|fullname|dob|address|postcode|state|vaccination_status|covid19_status|covid19_test_result|covid_19_test_date|dependant|dependant_relationship