#pragma once
using namespace std;
#include "./user_helper.cpp"
#include "./user_login.cpp"
#include "./user_register.cpp"
#include "./user_functions.cpp"
#include "../data_management/process_user_data.cpp"

void user_auth_menu(void);
void user_menu(string username);

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

void user_menu(string username)
{
    system("cls");
    system("Color 0A");
    int user_menu_choice;
    vector<user_data_struct> user_list = read_user_data();
    user_data_struct user = has_username_in_db(user_list, username);
    display_heading("USER MENU");
    cout << "\nWelcome " << user.fullname << "\n";
    cout << "\nCovid 19 Status : " << covid_19_status[user.covid19_status] << "\n";
    cout << "\nVaccination Status : " << (user.vaccination_status == "A" ? "Vaccinated" : "Unvaccinated") << "\n";
    vector<string> actions = notification(user.username);
    if (user.covid19_status == 1)
    {
        cout << "\nYour " << user.dependant_relationship << " is tested positive for COVID-19 \n";
    }
    if (actions.size() > 0)
    {
        cout << "\nActions center\n";
    }
    for (int i = 0; i < actions.size(); i++)
    {
        cout << i + 1 << ") " << actions[i] << "\n";
    }
    cout << "\n";

    vector<string> options = {"View Profile",
                              "Update COVID 19 Test",
                              "Update Profile",
                              "Apply Vaccination",
                              "Logout"};
    display_option(options);
    cout << "Please choose an option : ";
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
    {
        view_user_profile(user);
    }
    else if (user_menu_choice == 2)
    {
        update_covid19_test(user);
    }
    else if (user_menu_choice == 3)
    {
        update_profile(user);
    }
    else if (user_menu_choice == 4)
    {
        apply_vaccination(user);
    }
    else if (user_menu_choice == 999)
    {
        return;
    }
}