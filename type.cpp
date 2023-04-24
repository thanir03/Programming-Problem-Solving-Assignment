#include <string>
#include <vector>
#pragma once
using namespace std;

// all struct types used in this application
struct user_data_struct
{
    string username;
    string password;
    string phone_num;
    string ic;
    string fullname;
    string dob;
    string address;
    string postcode;
    int state;
    string vaccination_status;
    int covid19_status;
    string dependant;
    string dependant_relationship;
};

struct vac_center_data
{
    int state;
    string vac_center_name;
};

struct vacc_appoinment_data
{
    string username;
    string vac_center;
    string vac_date;
};

struct covid_19_stats
{
    int state;
    int quantity;
};

// covid-19 status
vector<string> covid_19_status = {
    "Confirmed Case", // 0
    "Close Contact",  // 1
    "Suspected Case", // 2
    "High Risk",      // 3
    "Low Risk",       // 4
};
// state list
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

// admin username list
vector<string> admin_list = {"admin1", "admin2", "admin3"};
