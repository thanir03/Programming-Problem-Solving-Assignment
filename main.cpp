#include <iostream>
#include <string>
#include <vector>
// files imported
#include "./user-interface/ui.cpp"
#include "./user/user_vaccination.cpp"
#include "./admin/admin_login.cpp"
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
