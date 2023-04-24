#include <string>
#include <vector>
#include <iostream>
#pragma once
// Imported files
#include "./user_helper.cpp"
#include "./user_login.cpp"
#include "./user_register.cpp"
#include "./user_functions.cpp"
#include "../data_management/process_user_data.cpp"
using namespace std;

// function prototype
void user_auth_menu(void);
void user_menu(string username);

// Imported Functions

void user_login(void);
void user_register(void);
vector<user_data_struct> read_user_data(void);
user_data_struct has_username_in_db(vector<user_data_struct> data, string username);
void check_dependant_covid_status(string username);
vector<string> get_action_list(string username);
void view_user_profile(user_data_struct user);
void update_covid19_test(user_data_struct user);
void update_profile(user_data_struct user);
void update_covid19_symptoms(user_data_struct user);
void apply_vaccination(user_data_struct user);
void display_option(vector<string> options);
void display_heading(string title);

// User authentication menu (consist of login and register)
void user_auth_menu(void)
{
    system("cls");
    display_heading("USER AUTHENTICATION MENU");
    int user_auth_choice;
    vector<string> option = {"LOGIN", "REGISTER", "EXIT"};
    cout << "Are you a user or admin ? \n";
    display_option(option);
    cout << "Enter your choice : ";
    cin >> user_auth_choice;
    if (cin.fail())
    {
        cout << "Invalid input\n";
        cin.clear();
        cin.ignore();
        user_auth_menu();
    }
    else if (user_auth_choice == 1)
    {
        user_login();
    }

    else if (user_auth_choice == 2)
    {
        user_register();
    }
    else if (user_auth_choice == 3)
    {
        return;
    }
    else
    {
        cout << "Invalid input\n";
        user_auth_menu();
    }
    cin.clear();
    cout << "\n";
    cout << "";
}

// User Menu once user is logged in
void user_menu(string username)
{
    system("cls");
    system("Color 0A");
    int user_menu_choice;
    check_dependant_covid_status(username);
    vector<user_data_struct> user_list = read_user_data();
    user_data_struct user = has_username_in_db(user_list, username);
    display_heading("USER MENU");
    cout << "\nWelcome " << user.fullname << "\n";
    cout << "\nCovid 19 Status : " << covid_19_status[user.covid19_status] << "\n";
    cout << "\nVaccination Status : " << (user.vaccination_status == "A" ? "Vaccinated" : "Unvaccinated") << "\n";
    vector<string> actions = get_action_list(user.username);
    if (user.covid19_status == 1)
    {
        cout << "\nYour " << user.dependant_relationship << " is tested positive for COVID-19 \n";
    }
    if (actions.size() > 0)
    {
        cout << "\nActions center\n";
        for (int i = 0; i < actions.size(); i++)
        {
            cout << i + 1 << ") " << actions[i] << "\n";
        }
    }
    cout << "\n";

    vector<string> options = {"View Profile",
                              "Update COVID 19 Test",
                              "Update Covid-19 Symptoms",
                              "Update Profile",
                              "Apply Vaccination",
                              "Logout"};
    display_option(options);
    cout << "\nPlease choose an option : ";
    cin >> user_menu_choice;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        user_menu_choice = 0;
    }
    while (user_menu_choice < 1 || user_menu_choice > options.size())
    {
        cout << "Invalid input";
        cout << "Please choose an option : ";
        cin >> user_menu_choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            user_menu_choice = 0;
        }
    }
    if (user_menu_choice == 1)
        view_user_profile(user);
    else if (user_menu_choice == 2)
        update_covid19_test(user);
    else if (user_menu_choice == 3)
        update_covid19_symptoms(user);
    else if (user_menu_choice == 4)
        update_profile(user);
    else if (user_menu_choice == 5)
        apply_vaccination(user);
    else
        return;
}