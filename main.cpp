#include <iostream>
#include <string>
#include <vector>
#include "./user-interface/ui.h"
#include "./user/user_vaccination.h"
#include "./admin/admin_login.h"
using namespace std;

// Function prototype

void run_program_again(bool *run_again);
void main_menu(void);

// Imported Functions

void user_auth_menu(void);
void admin_login(void);
void display_heading(string title);
void filter_vac_appoinment(void);

// function to request user to run again
void run_program_again(bool *run_again)
{
    char run_again_choice;
    cout << "Do you want to run again : (y/n) ";
    cin >> run_again_choice;
    if (run_again_choice == 'y')
        *run_again = true;
    else
        *run_again = false;
}

// main menu of the program
// user get to choose between user or admin
// filter_vac_appoinment filters the users that have already completed their appoinment
void main_menu(void)
{
    system("cls");
    system("Color 0B");
    filter_vac_appoinment();
    display_heading("Welcome to Covid-19 Tracking System");
    vector<string> option = {"USER",
                             "ADMIN",
                             "EXIT"};
    int choice;
    cout << "Are you a user or admin ? \n";
    display_option(option);
    cout << "Enter your choice : ";
    cin >> choice;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
    }
    while (choice < 1 || choice > option.size())
    {
        cout << "Enter your choice : ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
    }
    if (choice == 1)
        user_auth_menu();
    else if (choice == 2)
        admin_login();
    else if (choice == 3)
        return;
    cout << "\n";
}

// Main function (function that execute on program load)
int main(void)
{
    bool run_again = false;
    main_menu();
    run_program_again(&run_again);
    while (run_again)
    {
        main_menu();
        run_program_again(&run_again);
    }
    system("pause");
    return 0;
}

// Note before running this program
// 1. Please install g++ compiler first
// Please refer https://code.visualstudio.com/docs/cpp/config-mingw

// Compilation Command :

// g++ type.h data_management/process_user_data.cpp data_management/process_vaccination.cpp data_management/process_vaccination_center.cpp helper/date_helper.cpp helper/encryption.cpp helper/sorting.cpp user-interface/ui.cpp user/user_helper.cpp user/user_menu.cpp  user/user_vaccination.cpp user/user_login.cpp user/user_register.cpp user/user_functions.cpp admin/admin_menu.cpp admin/admin_functions.cpp admin/admin_login.cpp main.cpp -o main

// Please take note that it will take some time to compile because there are a lot of files

// Execution Command :

// start main.exe