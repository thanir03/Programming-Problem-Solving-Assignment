#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <vector>
#define confirmedCase 0
#define casualContact 1
#define suspectedCase 2
#define highRisk 3
#define lowRisk 4
#define vaccinatedStatus "A"
#define unvaccinatedStatus "B"
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
const vector<string> covid_19_status = {
    "Confirmed Case", // 0
    "Casual Contact", // 1
    "Suspected Case", // 2
    "High Risk",      // 3
    "Low Risk",       // 4
};
// state list
const vector<string> state_list = {
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
const vector<string> admin_list = {"admin1", "admin2", "admin3"};

#endif // TYPE_H