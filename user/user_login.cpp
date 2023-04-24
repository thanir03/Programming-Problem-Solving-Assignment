#include <string>
#include <vector>
#include <iostream>
#pragma once
// Imported files
#include "./user_helper.cpp"
#include "../data_management/process_user_data.cpp"
#include "./user_menu.cpp"
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
    display_heading("USER LOGIN");
    cout << "Enter your username : ";
    cin >> username;
    user_data_struct current_user_data;
    while (true)
    {
        current_user_data = has_username_in_db(data, username);
        if (current_user_data.username != "")
            break;
        cout << "\nUsername not in the database\n";
        cout << "Enter your username : ";
        cin >> username;
    }
    int password_attempt_count = 0;
    cout << "\n";
    cout << "Enter your password : ";
    cin >> password;
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
        cin >> password;
        password_attempt_count++;
    }

    user_menu(current_user_data.username);
}