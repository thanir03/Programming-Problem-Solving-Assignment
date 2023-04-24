#include <iostream>
#include <vector>
#include <string>
#pragma once
// Imported files
#include "../user-interface/ui.cpp"
#include "../admin/admin_functions.cpp"
using namespace std;

// Functions prototype
void admin_menu(void);

// Imported Functions
void view_covid19_positive(void);
void view_vaccination_center(void);
void view_covid19_stats(void);
void view_vaccination_appoinment(void);
void display_heading(string title);

// Admin menu for admin actions
void admin_menu()
{
    system("cls");
    system("Color 0A");
    int admin_menu_choice;
    display_heading("ADMIN MENU");
    vector<string> admin_options = {"View Covid-19 Positive Patient", "View Vaccination Centre", "View Covid-19 Statistics", "View Vaccination Appoinment", "Logout"};
    display_option(admin_options);
    cout << "Enter your option : ";
    cin >> admin_menu_choice;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        admin_menu_choice = 0;
    }
    while (admin_menu_choice < 1 || admin_menu_choice > admin_options.size())
    {
        cout << "Enter your option : ";
        cin >> admin_menu_choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            admin_menu_choice = 0;
        }
    }
    if (admin_menu_choice == 1)
        view_covid19_positive();
    else if (admin_menu_choice == 2)
        view_vaccination_center();
    else if (admin_menu_choice == 3)
        view_covid19_stats();
    else if (admin_menu_choice == 4)
        view_vaccination_appoinment();
    else
        return;
}