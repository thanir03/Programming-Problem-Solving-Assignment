#include <iostream>
#include <string>
#include <vector>
#pragma once
// Imported files
#include "./user_helper.cpp"
#include "./user_menu.cpp"
#include "../user-interface/ui.cpp"
#include "./user_register.cpp"
#include "../helper/date_helper.cpp"
#include "../user/user_vaccination.cpp"
#include "../type.cpp"
#define TWO_DAYS_IN_SECONDS 172800
using namespace std;

// Function prototype

void view_user_profile(user_data_struct user);
void update_profile(user_data_struct user);
vector<string> get_action_list(string username);
void update_covid19_symptoms(user_data_struct user);
bool validate_test_date(string date);

// Imported function prototype
void user_menu(string username);
vector<user_data_struct> read_user_data(void);
user_data_struct has_username_in_db(vector<user_data_struct> data, string username);
vacc_appoinment_data find_vac_app(string username);
void change_single_user_data(user_data_struct user);
time_t parse_string_date(string date);
void display_option(vector<string> options);
void display_heading(string title);
string read_postcode(void);
string read_phone_num(void);
void read_dependant(string *dependant, string *dependant_relationship, vector<user_data_struct> data);
int read_state(void);

// returning array of actions according to the user's covid-19 status
vector<string> get_action_list(string username)
{
    vector<user_data_struct> user_list = read_user_data();
    user_data_struct user = has_username_in_db(user_list, username);
    vector<string> actions = {};
    if (user.covid19_status == 0)
    {
        actions.push_back("Quarantine for 10 days");
        actions.push_back("Perform a Covid 19 Test after 10 days");
    }
    else if (user.covid19_status == 1 || user.covid19_status == 2)
    {
        actions.push_back("Perform a Covid 19 Test immediately");
        actions.push_back("Quarantine for 3 days");
    }
    if (user.vaccination_status == "B")
    {
        vacc_appoinment_data user_vac = find_vac_app(username);
        if (user_vac.username != "")
            actions.push_back("Your vaccination is on " + user_vac.vac_date + " at " + user_vac.vac_center);
        else
            actions.push_back("Apply for vaccination");
    }
    return actions;
}

// checking whether the user has dependant
// if the user has dependant and the dependant is a confirmed case , change the current user covid19 status to suspected case
void check_dependant_covid_status(string username)
{
    vector<user_data_struct> user_list = read_user_data();
    user_data_struct user = has_username_in_db(user_list, username);
    if (user.dependant == "0" || user.covid19_status == 0)
        return;
    user_data_struct dependant = has_username_in_db(user_list, user.dependant);
    if (dependant.covid19_status != 0 && user.covid19_status == 1)
        user.covid19_status = ((user.vaccination_status == "A") ? 4 : 3);
    if (dependant.covid19_status == 0)
        user.covid19_status = 1;
    change_single_user_data(user);
}

// validate test date
bool validate_test_date(string date)
{
    if (date.length() != 10)
    {
        return false;
    }
    if (date[2] != '/' && date[5] != '/')
        return false;
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    time_t formatted_date = parse_string_date(to_string(day) + "/" + to_string(month) + "/" + to_string(year));
    time_t current_time = time(0);
    if (formatted_date > current_time || current_time - formatted_date > TWO_DAYS_IN_SECONDS)
        return false;
    return true;
}

// allow user to update covid 19 test
// if the test is postive , update covid19 status to confirmed case
// else the covid19 status depends on the vaccination status of the user
void update_covid19_test(user_data_struct user)
{
    system("cls");
    display_heading("UPDATE COVID-19 TEST");
    char has_tested;
    cout << "Have you done the COVID-19 test ? (y/n) ";
    cin >> has_tested;
    while (cin.fail() || (tolower(has_tested) != 'y' && tolower(has_tested) != 'n'))
    {
        cin.clear();
        cin.ignore();
        cout << "\nInvalid Input\n";
        cout << "Have you done the COVID-19 test ? (y/n) ";
        cin >> has_tested;
    }

    if (tolower(has_tested) != 'y')
    {
        cout << "\nThis menu is to update your covid-19 test taken.\n";
    }
    else
    {
        string covid_19_test_date;
        char covid19_test_result;
        int covid19_status = user.covid19_status;
        cin.ignore();
        cout << "\nWhen was the COVID 19 test taken ? DD/MM/YYYY : ";
        getline(cin, covid_19_test_date);
        while (!validate_test_date(covid_19_test_date))
        {
            cout << "\nInvalid Date\n";
            cout << "When was the COVID 19 test taken ? ";
            getline(cin, covid_19_test_date);
        }

        cout << "\nP - Positive\n";
        cout << "\nN - Negative\n";
        cout << "\nWhat is the outcome of the test ? (P/N) : ";
        cin >> covid19_test_result;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            covid19_test_result = 'A';
        }
        while (toupper(covid19_test_result) != 'P' && toupper(covid19_test_result) != 'N')
        {
            cout << "\nP - Positive\n";
            cout << "\nN - Negative\n";
            cout << "\nWhat is the outcome of the test ? ";
            cin >> covid19_test_result;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                covid19_test_result = 'A';
            }
        }
        if (covid19_test_result == 'P')
            covid19_status = 0;
        else
            covid19_status = ((user.vaccination_status == "A") ? 4 : 3);
        cout << "\nThank you for updating your covid19 test.\n";
        user.covid19_status = covid19_status;
        change_single_user_data(user);
        system("pause");
        user_menu(user.username);
    }
}

// View user profile
void view_user_profile(user_data_struct user)
{
    int year = 1970 + (time(NULL) / 60 / 60 / 24 / 365);
    system("cls");
    display_heading("USER PROFILE");
    cout << "Full Name : " << user.fullname << "\n";
    cout << "Age : " << year - stoi(user.dob.substr(6, 4)) << "\n";
    cout << "Date of Birth : " << user.dob << "\n";
    cout << "Identity Number : " << user.ic << "\n";
    cout << "Address : " << user.address << " , " << user.postcode << " , " << state_list[user.state - 1] << "\n";
    cout << "Phone Number : " << user.phone_num << "\n";
    cout << "Vaccination Status : " << (user.vaccination_status == "A" ? "Vaccinated" : "Unvaccinated") << "\n";
    cout << "Covid 19 Status : " << covid_19_status[user.covid19_status] << "\n"
         << "\n";
    system("pause");
    user_menu(user.username);
}

// Update user profile
// user's are able to update their profile details
void update_profile(user_data_struct user)
{
    system("cls");
    vector<user_data_struct> user_list = read_user_data();
    display_heading("UPDATE PROFILE");
    vector<string> options = {"Phone Number", "Address", "Postcode", "Dependant", "State", "Back"};
    display_option(options);
    int user_option;
    cout << "Enter your option : ";
    cin >> user_option;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
    }
    while (user_option < 1 && user_option > options.size())
    {
        cout << "Invalid option";
        cout << "Enter your option : ";
        cin >> user_option;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            user_option = 0;
        }
    }
    string phone_num, address, postcode, dependant, dependant_relationship;
    int state;
    cin.clear();
    cin.ignore();
    switch (user_option)
    {
    case 1:
        phone_num = read_phone_num();
        user.phone_num = phone_num;
        break;
    case 2:
        address = read_address();
        user.address = address;
        break;
    case 3:
        postcode = read_postcode();
        user.postcode = postcode;
        break;
    case 4:
        read_dependant(&dependant, &dependant_relationship, user_list);
        user.dependant = dependant;
        user.dependant_relationship = dependant_relationship;
        break;
    case 5:
        state = read_state();
        user.state = state;
        break;
    case 6:
        system("pause");
        user_menu(user.username);
        return;
    }
    change_single_user_data(user);
    cout << "\nUser details updated successfully\n";
    system("pause");
    user_menu(user.username);
}

// Update user's covid 19 covid-19 symptoms
// if the user has flu , fever and cough and not confirmed or not closed contact , change the covid19 status to suspected case
// if the user does not have either one of the symptoms and not confirmed or not closed contact , change the covid19 status to high risk or low risk according to their vaccination status
void update_covid19_symptoms(user_data_struct user)
{
    system("cls");
    display_heading("UPDATE COVID-19 SYMPTOMS");
    char cough, fever, flu;
    cout << "Do you have flu ? (y/n) : ";
    cin >> flu;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
    }
    while (tolower(flu) != 'y' && tolower(flu) != 'n')
    {
        cout << "Do you have flu ? (y/n) : ";
        cin >> flu;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
    }
    cout << "Do you have cough ? (y/n) : ";
    cin >> cough;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
    }
    while (tolower(cough) != 'y' && tolower(cough) != 'n')
    {
        cout << "Do you have cough ? (y/n) : ";
        cin >> cough;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
    }
    cout << "Do you have fever ? (y/n) : ";
    cin >> fever;
    while (tolower(fever) != 'y' && tolower(fever) != 'n')
    {
        cout << "Do you have fever ? (y/n) : ";
        cin >> fever;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
    }
    if (tolower(flu) == 'y' && tolower(cough) == 'y' && tolower(fever) == 'y' && (user.covid19_status != 0 && user.covid19_status != 1))
        user.covid19_status = 2;
    else if (tolower(flu) == 'n' || tolower(cough) == 'n' || tolower(fever) == 'n' && (user.covid19_status != 0 && user.covid19_status != 1))
        user.covid19_status = (user.vaccination_status == "A" ? 4 : 3);
    change_single_user_data(user);
    cout << "\nSuccessfully updated your symptoms\n";
    system("pause");
    user_menu(user.username);
}