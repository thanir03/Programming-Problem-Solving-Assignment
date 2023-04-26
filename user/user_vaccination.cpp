#include <ctime>
#include <vector>
#include "./user_vaccination.h"
#include "../data_management/process_vaccination.h"
#include "../data_management/process_vaccination_center.h"
#include "../data_management/process_user_data.h"
#include "../helper/date_helper.h"
#include "./user_menu.h"
#include "../type.h"
#include "../user-interface/ui.h"
#define TWO_DAYS_IN_SECONDS 172800
using namespace std;

// Function prototype

void filter_vac_appoinment();
void change_vaccination_status(vector<vacc_appoinment_data> completed_vac_app);
vacc_appoinment_data find_vac_app(string username);
string get_vacc_date(user_data_struct user);
void display_vaccination_app(vacc_appoinment_data user_app);

// Function prototype from other files

vector<vacc_appoinment_data> read_vaccination_data();
bool write_vaccination_data(vector<user_data_struct>);
time_t parse_string_date(string date);
vector<vac_center_data> read_vacc_center_data(void);
bool add_vaccination_data(vacc_appoinment_data vac_app);
void user_menu(string username);

// filter the vaccination appoinment that have already occur
void filter_vac_appoinment(void)
{
    time_t current_time = time(0);
    vector<vacc_appoinment_data> vac_app = read_vaccination_data();
    vector<vacc_appoinment_data> incomplete_vac_app;
    vector<vacc_appoinment_data> completed_vac_app;
    for (int i = 0; i < vac_app.size(); i++)
    {
        time_t vac_date_in_seconds = parse_string_date(vac_app[i].vac_date);
        if (current_time <= vac_date_in_seconds)
            incomplete_vac_app.push_back(vac_app[i]);
        else
            completed_vac_app.push_back(vac_app[i]);
    }
    change_vaccination_status(completed_vac_app);
    write_vaccination_data(incomplete_vac_app);
}

// once the vaccination appoinment is completed , the user is changed to vaccinated status
void change_vaccination_status(vector<vacc_appoinment_data> completed_vac_app)
{
    vector<user_data_struct> user_list = read_user_data();
    for (int i = 0; i < completed_vac_app.size(); i++)
    {
        for (int j = 0; j < user_list.size(); j++)
        {
            if (user_list[j].username == completed_vac_app[i].username)
            {
                user_list[j].vaccination_status = vaccinatedStatus;
                if (user_list[j].covid19_status == highRisk)
                    user_list[j].covid19_status = lowRisk;
            }
        }
    }
    write_user_data(user_list);
}

// find the vaccination appoinment with username
vacc_appoinment_data find_vac_app(string username)
{
    vector<vacc_appoinment_data> vac_app_data = read_vaccination_data();
    for (int i = 0; i < vac_app_data.size(); i++)
    {
        if (vac_app_data[i].username == username)
        {
            return vac_app_data[i];
        }
    }
    return {};
}

// get vaccination date which is 2 days from current date
string get_vacc_date(user_data_struct user)
{
    time_t current_time = time(0) + TWO_DAYS_IN_SECONDS;
    return parse_date_object(current_time);
}

// display vaccination appoiment
void display_vaccination_app(vacc_appoinment_data user_app)
{
    cout << "\nYour vaccination appoinment\n";
    cout << "\nVaccination Center : " << user_app.vac_center << "\n";
    cout << "\nVaccination Date : " << user_app.vac_date << "\n";
}

// User registering for vaccination
// if the user is vaccinated , user is unable to register for vaccination
// if the user is already registerd , display the vaccination appoinment
// if the user is not yet registered , register the user for vaccination and display the vaccination appoinment
void apply_vaccination(user_data_struct user)
{
    system("cls");
    display_heading("Apply For Vaccination");
    if (user.vaccination_status == vaccinatedStatus)
    {
        cout << "\nYou are already vaccinated\n";
    }
    else
    {
        vacc_appoinment_data user_app = find_vac_app(user.username);
        if (user_app.username != "")
        {
            display_vaccination_app(user_app);
        }
        else
        {
            vector<vac_center_data> vac_center_list = read_vacc_center_data();
            string user_vac_center;
            for (int i = 0; i < vac_center_list.size(); i++)
            {
                if (vac_center_list[i].state == user.state)
                {
                    user_vac_center = vac_center_list[i].vac_center_name;
                    break;
                }
            }
            string user_vac_date = get_vacc_date(user);
            vacc_appoinment_data vac_app = {
                username : user.username,
                vac_center : user_vac_center,
                vac_date : user_vac_date
            };
            bool is_added = add_vaccination_data(vac_app);
            if (is_added)
                display_vaccination_app(vac_app);
            else
                cout << "Failed to add your record. Please try again";
        }
    }
}