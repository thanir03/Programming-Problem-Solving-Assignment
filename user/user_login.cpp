#include <string>
#include <vector>
#include <iostream>
#include "./user_helper.h"
#include "../data_management/process_user_data.h"
#include "./user_menu.h"
using namespace std;

// Function prototype

void user_login(void);

// Imported functions

void user_menu(string username);
vector<user_data_struct> read_user_data(void);
void display_heading(string title);
user_data_struct has_username_in_db(vector<user_data_struct> data, string username);

// Login menu to input username and password
void user_login(void)
{
    system("cls");
    vector<user_data_struct> data = read_user_data();
    string username, password;
    int user_login_attempt = 1;
    display_heading("USER LOGIN");
    cin.clear();
    cin.ignore();
    cout << "Enter your username : ";
    getline(cin, username);
    user_data_struct current_user_data;
    while (user_login_attempt < 3)
    {
        current_user_data = has_username_in_db(data, username);
        if (current_user_data.username != "")
            break;
        cout << "\nUsername not in the database\n";
        cout << "Enter your username : ";
        getline(cin, username);
        user_login_attempt++;
    }
    if (user_login_attempt == 3)
    {
        cout << "Too many attempts";
        return;
    }
    int password_attempt_count = 0;
    cout << "\n";
    cout << "Enter your password : ";
    getline(cin, password);
    password_attempt_count++;
    while (password != current_user_data.password)
    {
        cout << "\nInvalid Password\n";
        if (password_attempt_count == 3)
        {
            cout << "Too many attempts";
            return;
        }
        cout << "Enter your password : ";
        getline(cin, password);
        password_attempt_count++;
    }
    cout << "\nYou have successfully logged in \n";
    system("pause");
    user_menu(current_user_data.username);
}