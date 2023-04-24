#include <iostream>
#include <vector>
#include <string>
#pragma once
#include "../data_management/process_user_data.cpp"
#include "./user_helper.cpp"
#include "../type.cpp"
using namespace std;

// Function prototype

void user_register(void);
bool validate_state(int state);
bool validate_username(string word);
bool validate_ic(string ic);
string extract_dob_from_ic(string ic);
bool validate_name(string name);
bool validate_postcode(string postcode);
bool validate_address(string address);
bool validate_phone_num(string phone_num);
string read_username(vector<user_data_struct> data);
string read_password(void);
string read_phone_num(void);
string read_ic(void);
string read_fullname(void);
string read_address(void);
string read_postcode(void);
int read_state(void);
void read_dependant(string *dependant, string *dependant_relationship, vector<user_data_struct> data);
char read_vaccination_status(void);
char read_has_dependant(void);

// Imported Functions

vector<user_data_struct> read_user_data(void);
void display_heading(string title);
void user_login(void);
bool add_user_data(user_data_struct new_user);

// registering new user and writing user data into user.txt file
void user_register(void)
{
    system("cls");
    vector<user_data_struct> data = read_user_data();
    user_data_struct new_user_data = {};
    display_heading("USER REGISTRATION");
    string username = read_username(data);
    string password = read_password();
    string phone_num = read_phone_num();
    string ic = read_ic();
    string dob = extract_dob_from_ic(ic);
    string fullname = read_fullname();
    string address = read_address();
    string postcode = read_postcode();
    int state = read_state();
    string dependant, dependant_relationship;
    char has_dependant = read_has_dependant();
    if (has_dependant == 'y')
        read_dependant(&dependant, &dependant_relationship, data);
    else
    {
        dependant = "0";
        dependant_relationship = "0";
    }
    char vaccination_status = read_vaccination_status();
    new_user_data.username = username;
    new_user_data.postcode = postcode;
    new_user_data.password = password;
    new_user_data.dob = dob;
    new_user_data.ic = ic;
    new_user_data.fullname = fullname;
    new_user_data.vaccination_status = vaccination_status;
    new_user_data.state = state;
    new_user_data.address = address;
    new_user_data.phone_num = phone_num;
    new_user_data.dependant = dependant;
    new_user_data.dependant_relationship = dependant_relationship;
    new_user_data.covid19_status = (vaccination_status == 'A') ? 3 : 2;

    bool has_added = add_user_data(new_user_data);

    if (has_added)
    {
        user_login();
    }
    else
    {
        char try_again;
        cout << "Failed to register user";
        cout << "Do you want to try again ? (y/n) : ";
        cin >> try_again;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            try_again = 'n';
        }
        else if (tolower(try_again) == 'y')
        {
            user_register();
        }
    }
}

// validate whether state code is between 1 and 14
bool validate_state(int state)
{
    return state >= 1 && state <= 14;
}

// validate username is be at least 5 and doesnt contain a space
bool validate_username(string username)
{
    if (username.length() < 5)
        return false;
    for (int i = 0; i < username.length(); i++)
    {
        if (username[i] == ' ')
        {
            return false;
        }
    }
    return true;
}

// validating ic number
// ensure the date is valid and state is valid
bool validate_ic(string ic)
{
    if (ic.length() != 12)
        return false;
    for (int i = 0; i < ic.length(); i++)
    {
        if (!isdigit(ic[i]))
            return false;
    }
    int birth_year = stoi(ic.substr(0, 2));
    int birth_month = stoi(ic.substr(2, 2));
    int birth_day = stoi(ic.substr(4, 2));
    int state = stoi(ic.substr(6, 2));
    bool is_state_valid = validate_state(state);
    if (!is_state_valid)
        return false;
    if (birth_month < 1 || birth_month > 12)
        return false;

    int days_in_month;
    if (birth_month == 1 || birth_month == 3 || birth_month == 5 || birth_month == 7 || birth_month == 8 || birth_month == 10 || birth_month == 12)
        days_in_month = 31;
    else if (birth_month == 4 || birth_month == 6 || birth_month == 9 || birth_month == 11)
        days_in_month = 30;
    else
    {
        if ((birth_year % 4 == 0 && birth_year % 100 != 0) || birth_year % 400 == 0)
            days_in_month = 29;
        days_in_month = 28;
    }
    if (birth_day < 1 || birth_day > days_in_month)
        return false;
    return true;
}
// get date of birth from ic number
string extract_dob_from_ic(string ic)
{
    string year, date, month;
    string dob_from_ic = ic.substr(0, 6);
    // checking whether the year is in 21th century
    if (stoi(dob_from_ic.substr(0, 1)) <= 2)
        year = "20" + dob_from_ic.substr(0, 2);
    else
        year = "19" + dob_from_ic.substr(0, 2);
    month = dob_from_ic.substr(2, 2);
    date = dob_from_ic.substr(4, 2);
    return date + "/" + month + "/" + year;
}

// ensure name is valid
bool validate_name(string name)
{
    for (int i = 0; i < name.length(); i++)
    {
        if (!isalpha(name[i]))
            return false;
    }
    return true;
}
// ensure postcode is valid
bool validate_postcode(string postcode)
{
    if (postcode.length() != 5)
        return false;
    for (int i = 0; i < postcode.length(); i++)
    {
        if (!isdigit(postcode[i]))
            return false;
    }
    return true;
}

// ensure address is valid
bool validate_address(string address)
{
    return address.length() > 10;
}

// ensure phone number is valid
bool validate_phone_num(string phone_num)
{
    if (phone_num.length() < 10)
        return false;
    for (int i = 0; i < phone_num.length(); i++)
    {
        if (!isdigit(phone_num[i]))
            return false;
    }
    return true;
}

// get username from user and checking whether username exist in the user.txt file
string read_username(vector<user_data_struct> data)
{
    string username;
    cout << "\nExample : cristiano7 \n";
    cout << "Enter an unique username : ";
    cin.ignore();
    getline(cin, username);
    while (has_username_in_db(data, username).username != "" && username != "" || !validate_username(username))
    {
        cout << username;
        cout << "\nUsername already taken or Invalid Username\n";
        cout << "Enter an unique username : ";
        getline(cin, username);
    }
    return username;
}

// getting password from user
string read_password(void)
{
    string password;
    cout << "Enter a password : ";
    getline(cin, password);
    while (password.length() <= 5)
    {
        cout << password;
        cout << "\nPassword not long enough\n";
        cout << "Enter a password : ";
        getline(cin, password);
    }
    return password;
}

// getting phone number from user
string read_phone_num(void)
{
    string phone_num;
    cout << "\nExample : 0194798675\n";
    cout << "Enter your phone number : ";
    getline(cin, phone_num);
    while (!validate_phone_num(phone_num))
    {
        cout << "\nPhone Number invalid\n";
        cout << "Enter your phone number : ";
        getline(cin, phone_num);
    }
    return phone_num;
}

// reading user ic
string read_ic(void)
{
    string ic;
    cout << "\nExample : 0XXXXXXXXXXX\n";
    cout << "Enter your IC number : ";
    getline(cin, ic);
    while (!validate_ic(ic))
    {
        cout << ic;
        cout << "\nIC invalid\n";
        cout << "Enter your IC number : ";
        getline(cin, ic);
    }
    return ic;
}

// reading user fullname
string read_fullname(void)
{
    string fullname;
    cout << "\nExample : Thanirmalai Nagappan\n";
    cout << "Enter your Full name: ";
    getline(cin, fullname);
    while (validate_name(fullname))
    {
        cout << "\nInvalid name\n";
        cout << "Enter your Full name ";
        getline(cin, fullname);
    }
    return fullname;
}

// reading user address
string read_address(void)
{
    string address;
    cout << "\nExample : 41-1 Persiaran Lemak Taman Segar\n";
    cout << "Enter your address: ";
    getline(cin, address);
    while (!validate_address(address))
    {
        cout << "\nInvalid address\n";
        cout << "Enter your address: ";
        getline(cin, address);
    }
    return address;
}

// reading user postcode
string read_postcode(void)
{
    string postcode;
    cout << "\nExample : 56100\n";
    cout << "Enter your postcode : ";
    getline(cin, postcode);
    while (!validate_postcode(postcode))
    {
        cout << "\nInvalid postcode\n";
        cout << "Enter your postcode : ";
        getline(cin, postcode);
    }
    return postcode;
}

// reading user state
int read_state(void)
{
    int state;
    cout << endl;
    for (int i = 0; i < state_list.size(); i++)
    {
        cout << i + 1 << " : " << state_list[i] << endl;
    }
    cout << "\nExample : 14\n";
    cout << "Enter your state : ";
    cin >> state;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        state = -1;
    }
    while (!validate_state(state))
    {
        cout << "\nInvalid state\n";
        cout << "Enter your state : ";
        cin >> state;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            state = -1;
        }
    }
    return state;
}

// reading user dependant and ensuring user dependant is registered in our system
void read_dependant(string *dependant, string *dependant_relationship, vector<user_data_struct> data)
{
    cin.clear();
    cin.ignore();
    cout << "\nExample : cristiano7\n";
    cout << "Enter dependant username : ";
    getline(cin, *dependant);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        *dependant = "";
    }
    while (has_username_in_db(data, *dependant).username == "")
    {
        cout << "\n Username doesnt exist in database\n";
        cout << "Enter dependant username : ";
        getline(cin, *dependant);
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            *dependant = "";
        }
    }
    cout << "Enter dependant relationship : ";
    getline(cin, *dependant_relationship);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        *dependant_relationship = "";
    }
    while (*dependant_relationship == "")
    {
        cout << "Enter dependant relationship : ";
        getline(cin, *dependant_relationship);
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            *dependant_relationship = "";
        }
    }
}

// reading vaccination status from user
char read_vaccination_status(void)
{
    char vaccination_status;
    cout << "\n A - Vaccinated";
    cout << "\n B - Unvaccinated";
    cout << "\nEnter your vaccination status : ";
    cin >> vaccination_status;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        vaccination_status = 'C';
    }
    while (vaccination_status != 'A' && vaccination_status != 'B')
    {
        cout << "Invalid Vaccination Status";
        cout << "\nEnter your vaccination status : ";
        cin >> vaccination_status;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            vaccination_status = 'C';
        }
    }
    return vaccination_status;
}

// reading whether the user has dependant
char read_has_dependant(void)
{
    char has_dependant;
    cout << "Do you have a dependant registered (y/n) ? ";
    cin >> has_dependant;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        has_dependant = 'a';
    }

    while (has_dependant != 'y' && has_dependant != 'n')
    {
        cout << "\nInvalid input\n";
        cout << "Do you have a dependant registered (y/n) ? ";
        cin >> has_dependant;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            has_dependant = 'a';
        }
    }
    return has_dependant;
}
