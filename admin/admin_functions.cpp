#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#pragma once
// Imported files
#include "../user-interface/ui.cpp"
#include "../admin/admin_menu.cpp"
#include "../user/user_helper.cpp"
#include "../data_management/process_user_data.cpp"
#include "../helper/sorting.cpp"
#include "../type.cpp"
using namespace std;
// done

// Function Prototype
vector<user_data_struct> get_covid_19_positive(vector<user_data_struct> user_list);
void view_covid19_stats(void);
void view_covid19_positive(void);
vector<covid_19_stats> get_positive_stats(vector<user_data_struct> user_list);
vector<covid_19_stats> get_unvac_stats(vector<user_data_struct> user_list);
void view_vaccination_center(void);
void view_vaccination_appoinment(void);

// Imported Functions
void admin_menu();
vector<user_data_struct> read_user_data(void);
void quick_sort(vector<covid_19_stats> &arr, int start, int end);
void display_option(vector<string> options);
void display_heading(string title);
vector<vac_center_data> read_vacc_center_data(void);
vector<vacc_appoinment_data> read_vaccination_data(void);

// get the list of covid-19 positive patients
vector<user_data_struct> get_covid_19_positive(vector<user_data_struct> user_list)
{
    vector<user_data_struct> positive_patients;
    for (int i = 0; i < user_list.size(); i++)
    {
        if (user_list[i].covid19_status == 0)
        {
            positive_patients.push_back(user_list[i]);
        }
    }
    return positive_patients;
}

// view covid-19 positive patients
void view_covid19_positive(void)
{
    system("cls");
    system("Color 0A");
    display_heading("View Covid 19 Positive Patients");
    vector<user_data_struct> user_list = read_user_data();
    vector<user_data_struct> positive_patients = get_covid_19_positive(user_list);
    cout << "\n"
         << left << setw(30) << "Name" << setw(20) << "State\n";
    cout << "\n";
    for (int i = 0; i < positive_patients.size(); i++)
    {
        cout << left << setw(30) << positive_patients[i].fullname << setw(20) << state_list[positive_patients[i].state - 1] << "\n";
    }
    system("pause");
    admin_menu();
}

// get covid 19 positive patients according to the states
// sort the states by number of positive patients
vector<covid_19_stats> get_positive_stats(vector<user_data_struct> user_list)
{
    vector<covid_19_stats> positive_patient_stats;
    for (int i = 0; i < 14; i++)
        positive_patient_stats.push_back({state : i, quantity : 0});
    for (int i = 0; i < user_list.size(); i++)
    {
        if (user_list[i].covid19_status == 0)
        {
            (positive_patient_stats[user_list[i].state - 1].quantity)++;
        }
    }
    quick_sort(positive_patient_stats, 0, positive_patient_stats.size() - 1);
    return positive_patient_stats;
}
// get unvaccinated patients according to the states
// sort the states by number of unvaccinated patients
vector<covid_19_stats> get_unvac_stats(vector<user_data_struct> user_list)
{
    vector<covid_19_stats> unvac_patients;
    for (int i = 0; i < 14; i++)
    {
        unvac_patients.push_back({state : i, quantity : 0});
    }
    for (int i = 0; i <= user_list.size() - 1; i++)
    {
        if (user_list[i].vaccination_status == "B")
        {
            (unvac_patients[user_list[i].state - 1].quantity)++;
        }
    }
    quick_sort(unvac_patients, 0, unvac_patients.size() - 1);
    return unvac_patients;
}

// view covid-19 stats
void view_covid19_stats(void)
{
    system("cls");
    display_heading("View Covid-19 Statistics");
    vector<user_data_struct> user_list = read_user_data();
    vector<string> options = {"View Covid-19 Positive Patients", "View Unvaccinated Patients"};
    int admin_option;
    display_option(options);
    cout << "\nEnter your option : ";
    cin >> admin_option;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
    }
    while (admin_option < 1 || admin_option > options.size())
    {
        cout << "\nInvalid option\n";
        cout << "\nEnter your option : \n";
        cin >> admin_option;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
    }
    vector<covid_19_stats> stats;
    if (admin_option == 1)
    {
        stats = get_positive_stats(user_list);
    }
    else if (admin_option == 2)
    {
        stats = get_unvac_stats(user_list);
    }
    string option_type = (admin_option == 1 ? "Covid-19 Patients" : "Unvaccinated Users");
    cout << "\n";
    system("cls");
    display_heading(option_type);
    cout << "\n"
         << left << setw(30) << "State" << setw(20) << "Number of " + option_type << "\n\n";

    for (int i = stats.size() - 1; i >= 0; i--)
    {
        cout << left << setw(30) << state_list[i] << setw(20) << stats[i].quantity << "\n";
    }
    system("pause");
    admin_menu();
}

// View all the vaccination centers
void view_vaccination_center(void)
{
    system("cls");
    display_heading("View Vaccination Center");
    vector<vac_center_data> vac_center_list = read_vacc_center_data();
    cout << left << setw(20) << "State" << setw(20) << "Vaccination Center\n";
    for (int i = 0; i < vac_center_list.size(); i++)
    {
        cout << left << setw(30) << state_list[vac_center_list[i].state - 1] << setw(20) << vac_center_list[i].vac_center_name << "\n";
    }
    system("pause");
    admin_menu();
}

// View all the vaccination appoinment
void view_vaccination_appoinment(void)
{
    system("cls");
    display_heading("View Vaccination Appoinment");
    vector<vacc_appoinment_data> vac_app_list = read_vaccination_data();
    bool has_vac_app = vac_app_list.size() > 0;
    if (vac_app_list.size() > 0)
    {

        cout << left << setw(20) << "Username" << setw(20) << "Vaccination Center" << setw(20) << "Vaccination Date\n";
        for (int i = 0; i < vac_app_list.size(); i++)
        {
            cout << left << setw(20) << vac_app_list[i].username << setw(20) << vac_app_list[i].vac_center << setw(20) << vac_app_list[i].vac_date << "\n";
        }
    }
    else
        cout << "\nThere is no vaccination appoinments\n";
    system("pause");
    admin_menu();
}