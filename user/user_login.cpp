#pragma once
using namespace std;
#include "./user_helper.cpp"
#include "../data_management/process_user_data.cpp"
#include "./user_menu.cpp"
void user_login(void);
void user_menu(string username);

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
    cout << "\n";
    cout << "Enter your password : ";
    cin >> password;
    cout << current_user_data.username << current_user_data.password << "\n";
    if (password != current_user_data.password)
    {
        cout << "\nInvalid Password\n";
        return;
    }

    user_menu(current_user_data.username);
}