#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#define user_file "data/users.txt"
#include "./user-interface/ui.cpp"
#include "./user/user_menu.cpp"
// #include "./admin/admin.cpp"
using namespace std;
void run_program_again(bool *run_again);
void main_menu(void);

void run_program_again(bool *run_again)
{
    char run_again_choice;
    cout << "Do you want to run again : (y/n) ";
    cin >> run_again_choice;
    if (run_again_choice == 'y')
    {
        *run_again = true;
    }
    else
    {
        *run_again = false;
    }
}

void main_menu(void)
{
    system("cls");
    system("Color 0B");
    display_heading("Welcome to MYSEJAHTERA");
    vector<string> option = {"USER",
                             "ADMIN",
                             "EXIT"};

    int choice;
    cout << "Are you a user or admin ? \n";
    display_option(option);
    cout << "Enter your choice : ";
    cin >> choice;
    cin.clear();
    if (choice == 1)
    {
        user_auth_menu();
    }

    else if (choice == 2)
    {
        // admin_login();
    }
    else if (choice == 3)
    {
        return;
    }
    else
    {
        cout << "Invalid input\n";
        cin.clear();
        cin.ignore();
        main_menu();
    }
    cout << "\n";
}

// void encryptString(void)
// {
//     string str = "hello world";

//     for (int i = 0; i < str.length(); i++)
//     {
//         str[i] = str[i] + 2;
//     }
//     cout << str;
// }
// void decryptString(void)
// {
//     string str = "jgnnq\"yqtnf";

//     for (int i = 0; i < str.length(); i++)
//     {
//         str[i] = str[i] - 2;
//     }
//     cout << str;
// }

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
    read_user_data();
    system("pause");
    return 0;
}
