#include <iostream>
#include <vector>
#include "../user-interface/ui.h"
#include "../admin/admin_menu.h"
#include "../type.h"
using namespace std;

// Function prototype

bool has_username_in_admin_list(string username);
void admin_login(void);

// Imported Functions

void display_heading(string title);
void admin_menu();

// checking whether the admin username is in the vector
bool has_username_in_admin_list(string username)
{
    for (int i = 0; i < admin_list.size(); i++)
    {
        if (admin_list[i] == username)
        {
            cout << "has username";
            return true;
        }
    }
    return false;
}

// function to allow admin to log in once the password and username match
void admin_login(void)
{
    system("cls");
    string username, password;
    int username_attempt = 1;
    int password_attempt = 1;
    display_heading("ADMIN LOGIN");
    cin.ignore();
    cin.clear();
    cout << "\nUsername: ";
    getline(cin, username);
    while (username_attempt < 3 && !has_username_in_admin_list(username))
    {
        cout << "\nInvalid username\n";
        cout << "\nUsername: ";
        getline(cin, username);
        if (cin.fail())
        {

            cin.ignore();
            cin.clear();
        }
        username_attempt++;
    }
    if (username_attempt == 3)
    {
        cout << "Too many attempts";
        return;
    }
    cout << "\nPassword: ";
    getline(cin, password);
    while (password_attempt < 3 && password != "password")
    {
        cout << "\nInvalid Password\n";
        cout << "\nPassword: ";
        getline(cin, password);
        if (cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        password_attempt++;
    }

    if (password_attempt == 3)
    {
        cout << "\nToo many attempts\n";
        return;
    }
    admin_menu();
}