#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include <cmath>
#include <fstream>
#define encryption_key 3
#define splitter '|'
#define user_file "data/users.txt"
#define vac_center_file "data/vaccination_center.txt"
#define vaccination_data_file "data/vaccination.txt"
#define confirmedCase 0
#define casualContact 1
#define suspectedCase 2
#define highRisk 3
#define lowRisk 4
#define vaccinatedStatus "A"
#define unvaccinatedStatus "B"
using namespace std;

// Function prototype
// ui
void display_heading(string title);
void display_option(vector<string> options);
// date
time_t parse_string_date(string date);
string parse_date_object(time_t date);
// encryption
string decrypt(string str, int key);
string encrypt(string str, int key);
// process_user_data
struct user_data_struct process_single_user_data(string line);
vector<user_data_struct> read_user_data(void);
void write_user_data(vector<user_data_struct> user_data);
bool add_user_data(user_data_struct new_user);
// process_vac_center
struct vac_center_data process_vac_centre_data(string single_line);
vector<vac_center_data> read_vacc_center_data(void);
// process vac_appoinment
struct vacc_appoinment_data process_vac_appoinment_data(string line);
vector<vacc_appoinment_data> read_vaccination_data(void);
bool write_vaccination_data(vector<vacc_appoinment_data> vac_app_list);
bool add_vaccination_data(vacc_appoinment_data vac_app);
void update_covid19_test(user_data_struct user);
// user menu
void user_auth_menu(void);
void user_menu(string username);
// user login
void user_login(void);
// user helper
user_data_struct has_username_in_db(vector<user_data_struct> data, string username);
void change_single_user_data(user_data_struct user);
// user function
void view_user_profile(user_data_struct user);
void update_profile(user_data_struct user);
vector<string> get_action_list(string username);
void update_covid19_symptoms(user_data_struct user);
bool validate_test_date(string date);
void check_dependant_covid_status(string username);
// user vaccination
void filter_vac_appoinment();
void change_vaccination_status(vector<vacc_appoinment_data> completed_vac_app);
vacc_appoinment_data find_vac_app(string username);
string get_vacc_date(user_data_struct user);
void display_vaccination_app(vacc_appoinment_data user_app);
void apply_vaccination(user_data_struct user);
// main
void run_program_again(bool *run_again);
void main_menu(void);
// user register
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
string read_vaccination_status(void);
char read_has_dependant(void);
// admin login
bool has_username_in_admin_list(string username);
void admin_login(void);
// admin functions
vector<user_data_struct> get_covid_19_positive(vector<user_data_struct> user_list);
void view_covid19_stats(void);
void view_covid19_positive(void);
vector<struct covid_19_stats> get_positive_stats(vector<user_data_struct> user_list);
vector<struct covid_19_stats> get_unvac_stats(vector<user_data_struct> user_list);
void view_vaccination_center(void);
void view_vaccination_appoinment(void);
// admin menu
void admin_menu(void);
//  main function
int main(void);

// structure for users_data
struct user_data_struct
{
    string username{};
    string password{};
    string phone_num{};
    string ic{};
    string fullname{};
    string dob{};
    string address{};
    string postcode{};
    int state{};
    string vaccination_status{};
    int covid19_status{};
    string dependant{};
    string dependant_relationship{};
};

// structure for vaccination_center
struct vac_center_data
{
    int state{};
    string vac_center_name{};
};

// structure for vaccination_appoinment
struct vacc_appoinment_data
{
    string username{};
    string vac_center{};
    string vac_date{};
};

// structure for covid-19-stats
struct covid_19_stats
{
    int state;
    int quantity;
};

// covid-19 status
const vector<string> covid_19_status = {
    "Confirmed Case", // 0
    "Casual Contact", // 1
    "Suspected Case", // 2
    "High Risk",      // 3
    "Low Risk",       // 4
};
// state list
const vector<string> state_list = {
    "Johor",
    "Kedah",
    "Kelantan",
    "Melaka",
    "Negeri Sembilan",
    "Pahang",
    "Penang",
    "Perak",
    "Perlis",
    "Selangor",
    "Terengganu",
    "Sabah",
    "Sarawak",
    "Kuala Lumpur",
};

// list of admin usernames
const vector<string> admin_list = {"admin1", "admin2", "admin3"};

// main function to run the program
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

// main menu to select whether user is admin or normal user
void main_menu(void)
{
    system("cls");
    system("Color 0B");
    // filter_vac_appoinment();
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

// determine whether user wants to run the program again
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

// display heading of the program
void display_heading(string title)
{
    cout << "\t=================================================================\n";
    cout << "\t" << title << "\n";
    cout << "\t=================================================================\n\n";
}

// Display options to be selected by users
void display_option(vector<string> options)
{
    for (int i = 0; i < options.size(); i++)
    {
        cout << "<" << i + 1 << "> " << options[i] << "\n";
    }
}

// convert date from string to time in seconds
time_t parse_string_date(string date)
{
    int day, month, year;
    vector<int> date_vector;
    string date_value;
    for (int i = 0; i < date.length(); i++)
    {
        if (date[i] == '/')
        {
            date_vector.push_back(stoi(date_value));
            date_value = "";
            continue;
        }
        date_value += date[i];
    }
    date_vector.push_back(stoi(date_value));
    day = date_vector[0];
    month = date_vector[1];
    year = date_vector[2];
    cout << day << month << year;
    tm date_struct{};
    date_struct.tm_mday = day;
    date_struct.tm_mon = month - 1;
    date_struct.tm_year = year - 1900;
    time_t date_time = mktime(&date_struct);
    return date_time;
}

// convert time in seconds to formatted date strings
string parse_date_object(time_t date)
{
    struct tm local_time;
    localtime_s(&local_time, &date);
    return to_string(local_time.tm_mday) + "/" + to_string(local_time.tm_mon + 1) + "/" + to_string(local_time.tm_year + 1900);
}

// Decrypt string with a key (used for password decryption)
string decrypt(string str, int key)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] -= key;
    }
    return str;
}

// Encrypt string with a key (used for password decryption)
string encrypt(string str, int key)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] += key;
    }
    return str;
}

// sorting algorithm to sort an array according to quantity of covid-19-stats
// Time complexity : O(n log n)
// Space Complexity : O(log n)
void quick_sort(vector<covid_19_stats> &arr, int start, int end)
{
    if (start >= end)
        return;
    int left = start;
    int right = end;
    int pivot = (left + right) / 2;
    swap(arr[left], arr[pivot]);
    left++;
    pivot = start;
    while (left <= right)
    {
        if (arr[left].quantity > arr[pivot].quantity && arr[right].quantity < arr[pivot].quantity)
            swap(arr[left], arr[right]);
        if (arr[left].quantity <= arr[pivot].quantity)
            left++;
        if (arr[right].quantity >= arr[pivot].quantity)
            right--;
    }
    swap(arr[pivot], arr[right]);
    quick_sort(arr, start, right - 1);
    quick_sort(arr, left, end);
}

// convert line from text file into a object instance
user_data_struct process_single_user_data(string line)
{
    vector<string> vectorData;
    string singleData = "";
    int idx = 0;
    while (idx < line.length())
    {
        if (line[idx] == splitter)
        {
            vectorData.push_back(singleData);
            singleData = "";
        }
        else
        {
            singleData += line[idx];
        }
        ++idx;
    }
    vectorData.push_back(singleData);
    singleData = "";
    user_data_struct single_user_data;
    single_user_data.username = vectorData[0];
    single_user_data.password = decrypt(vectorData[1], encryption_key);
    single_user_data.phone_num = vectorData[2];
    single_user_data.ic = vectorData[3];
    single_user_data.fullname = vectorData[4];
    single_user_data.dob = vectorData[5];
    single_user_data.address = vectorData[6];
    single_user_data.postcode = vectorData[7];
    single_user_data.state = stoi(vectorData[8]);
    single_user_data.vaccination_status = vectorData[9];
    single_user_data.covid19_status = stoi(vectorData[10]);
    single_user_data.dependant = vectorData[11];
    single_user_data.dependant_relationship = vectorData[12];
    return single_user_data;
}

// read user.txt file
vector<user_data_struct> read_user_data(void)
{
    vector<user_data_struct> data;
    fstream database;
    database.open(user_file);
    if (database.is_open())
    {

        int line_number = 0;
        string user_data_line;
        while (!database.eof())
        {
            getline(database, user_data_line);
            if (user_data_line == "")
            {
                break;
            }
            data.push_back(process_single_user_data(user_data_line));
        }
        database.close();
        return data;
    }
    else
    {
        cout << "Cannot open file\n";
        return {};
    }
}

// rewriting the entire user.txt file
void write_user_data(vector<user_data_struct> user_data)
{
    fstream user_db;
    user_db.open(user_file, ios::out);
    if (user_db.is_open())
    {
        for (int i = 0; i < user_data.size(); i++)
        {
            user_data_struct new_user = user_data[i];
            user_db << new_user.username << splitter << encrypt(new_user.password, encryption_key) << splitter << new_user.phone_num << splitter << new_user.ic << splitter << new_user.fullname << splitter << new_user.dob << splitter << new_user.address << splitter << new_user.postcode << splitter << new_user.state << splitter << new_user.vaccination_status << splitter << new_user.covid19_status << splitter << new_user.dependant << splitter << new_user.dependant_relationship << "\n";
        }
    }
}

// appending new user data into user.txt file
bool add_user_data(user_data_struct new_user)
{
    fstream user_db;
    user_db.open(user_file, ios::app);
    if (user_db.is_open())
    {
        user_db << new_user.username << splitter << encrypt(new_user.password, encryption_key) << splitter << new_user.phone_num << splitter << new_user.ic << splitter << new_user.fullname << splitter << new_user.dob << splitter << new_user.address << splitter << new_user.postcode << splitter << new_user.state << splitter << new_user.vaccination_status << splitter << new_user.covid19_status << splitter << new_user.dependant << splitter << new_user.dependant_relationship << "\n";
        user_db.close();
        return true;
    }
    else
    {
        cout << "Adding user to the file failed";
        return false;
    }
}

// convert line into instance of object of vaccination center data
vac_center_data process_vac_centre_data(string single_line)
{
    vector<string> data_list = {};
    string data;
    for (int i = 0; i < single_line.length(); i++)
    {
        if (single_line[i] == '|')
        {
            data_list.push_back(data);
            data = "";
            continue;
        }
        data += single_line[i];
    }
    data_list.push_back(data);
    vac_center_data vac_center;
    vac_center.state = stoi(data_list[0]);
    vac_center.vac_center_name = data_list[1];
    return vac_center;
}

// reading the vaccination_center.txt file
vector<vac_center_data> read_vacc_center_data(void)
{
    fstream vac_center_db;
    vac_center_db.open(vac_center_file, ios::in);
    if (!vac_center_db.is_open())
    {
        cout << "Failed to open the vaccination center database";
        return {};
    }
    vector<vac_center_data> list_of_vac_center = {};
    string single_line;
    while (!vac_center_db.eof())
    {
        getline(vac_center_db, single_line);
        if (single_line == "")
            break;
        list_of_vac_center.push_back(process_vac_centre_data(single_line));
    }
    return list_of_vac_center;
}
// convert line into instance of object of vaccination data
vacc_appoinment_data process_vac_appoinment_data(string line)
{
    int i = 0;
    string data;
    vector<string> data_list = {};
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '|')
        {
            data_list.push_back(data);
            data = "";
            continue;
        }
        data += line[i];
    }
    data_list.push_back(data);
    vacc_appoinment_data vac_app_list;
    vac_app_list.username = data_list[0];
    vac_app_list.vac_center = data_list[1];
    vac_app_list.vac_date = data_list[2];
    return vac_app_list;
}

// read vaccination data
vector<vacc_appoinment_data> read_vaccination_data(void)
{
    fstream vac_db;
    vac_db.open(vaccination_data_file, ios::in);
    if (!vac_db.is_open())
    {
        cout << "Unable to read data";
    }
    string line;
    vector<vacc_appoinment_data> vacc_app_list;
    while (!vac_db.eof())
    {
        getline(vac_db, line);
        if (line == "")
        {
            break;
        }
        vacc_app_list.push_back(process_vac_appoinment_data(line));
    }
    vac_db.close();
    return vacc_app_list;
}

// rewrite the entire vaccination.txt file
bool write_vaccination_data(vector<vacc_appoinment_data> vac_app_list)
{
    fstream vac_db;
    vac_db.open(vaccination_data_file, ios::out);
    if (!vac_db.is_open())
    {
        cout << "Unable to read data";
        return false;
    }
    for (int i = 0; i < vac_app_list.size(); i++)
    {
        vac_db << vac_app_list[i].username << splitter << vac_app_list[i].vac_center << splitter << vac_app_list[i].vac_date << "\n";
    }
    vac_db.close();
    return true;
}

// append new vaccination data to the end of the file
bool add_vaccination_data(vacc_appoinment_data vac_app)
{
    fstream vac_db;
    vac_db.open(vaccination_data_file, ios::app);
    if (!vac_db.is_open())
    {
        cout << "Unable to read data";
        return false;
    }
    vac_db << vac_app.username << splitter << vac_app.vac_center << splitter << vac_app.vac_date << "\n";
    vac_db.close();
    return true;
}
///////////////////////////////////////////////////////////// USER

// checking whether username exist in user.txt
user_data_struct has_username_in_db(vector<user_data_struct> data, string username)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].username == username)
            return data[i];
    }
    return {};
}

// reading the user file , changing the users data and rewriting the file
void change_single_user_data(user_data_struct user)
{
    vector<user_data_struct> user_list = read_user_data();
    for (int i = 0; i < user_list.size(); i++)
    {
        if (user_list[i].username == user.username)
        {
            user_list[i] = user;
        }
    }
    write_user_data(user_list);
}

void user_auth_menu(void)
{
    system("cls");
    display_heading("USER AUTHENTICATION MENU");
    int user_auth_choice;
    vector<string> option = {"LOGIN", "REGISTER", "EXIT"};
    cout << "Are you a user or admin ? \n";
    display_option(option);
    cout << "Enter your choice : ";
    cin >> user_auth_choice;
    if (cin.fail())
    {
        cout << "Invalid input\n";
        cin.clear();
        cin.ignore();
        user_auth_menu();
    }
    else if (user_auth_choice == 1)
    {
        user_login();
    }

    else if (user_auth_choice == 2)
    {
        user_register();
    }
    else if (user_auth_choice == 3)
    {
        return;
    }
    else
    {
        cout << "Invalid input\n";
        user_auth_menu();
    }
    cin.clear();
    cout << "\n";
    cout << "";
}

// User Menu once user is logged in
void user_menu(string username)
{
    system("cls");
    system("Color 0A");
    int user_menu_choice;
    check_dependant_covid_status(username);
    vector<user_data_struct> user_list = read_user_data();
    user_data_struct user = has_username_in_db(user_list, username);
    display_heading("USER MENU");
    cout << "\nWelcome " << user.fullname << "\n";
    cout << "\nCovid 19 Status : " << covid_19_status[user.covid19_status] << "\n";
    cout << "\nVaccination Status : " << (user.vaccination_status == "A" ? "Vaccinated" : "Unvaccinated") << "\n";
    vector<string> actions = get_action_list(user.username);
    if (user.covid19_status == 1)
    {
        cout << "\nYour " << user.dependant_relationship << " is tested positive for COVID-19 \n";
    }
    if (actions.size() > 0)
    {
        cout << "\nActions center\n";
        for (int i = 0; i < actions.size(); i++)
        {
            cout << i + 1 << ") " << actions[i] << "\n";
        }
    }
    cout << "\n";

    vector<string> options = {"View Profile",
                              "Update COVID 19 Test",
                              "Update Covid-19 Symptoms",
                              "Update Profile",
                              "Apply Vaccination",
                              "Logout"};
    display_option(options);
    cout << "\nPlease choose an option : ";
    cin >> user_menu_choice;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        user_menu_choice = 0;
    }
    while (user_menu_choice < 1 || user_menu_choice > options.size())
    {
        cout << "Invalid input";
        cout << "Please choose an option : ";
        cin >> user_menu_choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            user_menu_choice = 0;
        }
    }
    if (user_menu_choice == 1)
        view_user_profile(user);
    else if (user_menu_choice == 2)
        update_covid19_test(user);
    else if (user_menu_choice == 3)
        update_covid19_symptoms(user);
    else if (user_menu_choice == 4)
        update_profile(user);
    else if (user_menu_choice == 5)
        apply_vaccination(user);
    else
        return;
    system("pause");
    user_menu(user.username);
}

// Prompting username and password to log in user
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

// register user by prompting all user details  and adding the user to the end of the file
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
    string vaccination_status = read_vaccination_status();
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
    new_user_data.covid19_status = (vaccination_status == vaccinatedStatus) ? lowRisk : highRisk;

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
string read_vaccination_status(void)
{
    string vaccination_status;
    cout << "\n A - Vaccinated";
    cout << "\n B - Unvaccinated";
    cout << "\nEnter your vaccination status : ";
    cin >> vaccination_status;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        vaccination_status = "C";
    }
    while (vaccination_status != vaccinatedStatus && vaccination_status != unvaccinatedStatus)
    {
        cout << "Invalid Vaccination Status";
        cout << "\nEnter your vaccination status : ";
        cin >> vaccination_status;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            vaccination_status = "C";
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

// getting a list of action according to covid19 status and vaccination status
vector<string> get_action_list(string username)
{
    vector<user_data_struct> user_list = read_user_data();
    user_data_struct user = has_username_in_db(user_list, username);
    vector<string> actions = {};
    if (user.covid19_status == confirmedCase)
    {
        actions.push_back("Quarantine for 10 days");
        actions.push_back("Perform a Covid 19 Test after 10 days");
    }
    else if (user.covid19_status == casualContact || user.covid19_status == suspectedCase)
    {
        actions.push_back("Perform a Covid 19 Test immediately");
        actions.push_back("Quarantine for 3 days");
    }
    if (user.vaccination_status == unvaccinatedStatus)
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
// if the user has dependant and the dependant is a confirmed case , change the current user covid19 status to casual contact
void check_dependant_covid_status(string username)
{
    vector<user_data_struct> user_list = read_user_data();
    user_data_struct user = has_username_in_db(user_list, username);
    if (user.dependant == "0" || user.covid19_status == 0)
        return;
    user_data_struct dependant = has_username_in_db(user_list, user.dependant);
    if (dependant.covid19_status != 0 && user.covid19_status == 1)
        user.covid19_status = ((user.vaccination_status == vaccinatedStatus) ? lowRisk : highRisk);
    if (dependant.covid19_status == confirmedCase)
        user.covid19_status = casualContact;
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
    if (formatted_date > current_time || current_time - formatted_date > 172800)
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
            cout << "\nInvalid Date or Date exceeded 1 day limit from today\n";
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
            covid19_status = confirmedCase;
        else
            covid19_status = ((user.vaccination_status == vaccinatedStatus) ? lowRisk : highRisk);
        cout << "\nThank you for updating your covid19 test.\n";
        user.covid19_status = covid19_status;
        change_single_user_data(user);
    }
}

// View user profile
void view_user_profile(user_data_struct user)
{
    time_t year = 1970 + (time(NULL) / 60 / 60 / 24 / 365);
    system("cls");
    display_heading("USER PROFILE");
    cout << "Full Name : " << user.fullname << "\n";
    cout << "Age : " << year - stoi(user.dob.substr(6, 4)) << "\n";
    cout << "Date of Birth : " << user.dob << "\n";
    cout << "Identity Number : " << user.ic << "\n";
    cout << "Address : " << user.address << " , " << user.postcode << " , " << state_list[user.state - 1] << "\n";
    cout << "Phone Number : " << user.phone_num << "\n";
    cout << "Vaccination Status : " << (user.vaccination_status == vaccinatedStatus ? "Vaccinated" : "Unvaccinated") << "\n";
    cout << "Covid 19 Status : " << covid_19_status[user.covid19_status] << "\n"
         << "\n";
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
    if (tolower(flu) == 'y' && tolower(cough) == 'y' && tolower(fever) == 'y' && (user.covid19_status != confirmedCase && user.covid19_status != casualContact))
        user.covid19_status = suspectedCase;
    else if ((tolower(flu) == 'n' || tolower(cough) == 'n' || tolower(fever) == 'n') && (user.covid19_status != confirmedCase && user.covid19_status != casualContact))
        user.covid19_status = (user.vaccination_status == vaccinatedStatus ? lowRisk : highRisk);
    change_single_user_data(user);
    cout << "\nSuccessfully updated your symptoms\n";
}

// filter vaccination appoinment by checking whether the vaccination date exceeding current data
void filter_vac_appoinment(void)
{
    time_t current_time = time(0);
    vector<vacc_appoinment_data> vac_app = read_vaccination_data();
    vector<vacc_appoinment_data> incomplete_vac_app;
    vector<vacc_appoinment_data> completed_vac_app;
    for (int i = 0; i < vac_app.size(); i++)
    {
        time_t vac_date_in_seconds = parse_string_date(vac_app[i].vac_date);
        if (current_time <= vac_date_in_seconds)
            incomplete_vac_app.push_back(vac_app[i]);
        else
            completed_vac_app.push_back(vac_app[i]);
    }
    change_vaccination_status(completed_vac_app);
    write_vaccination_data(incomplete_vac_app);
}

// once the vaccination appoinment is completed , the user is changed to vaccinated status
void change_vaccination_status(vector<vacc_appoinment_data> completed_vac_app)
{
    vector<user_data_struct> user_list = read_user_data();
    for (int i = 0; i < completed_vac_app.size(); i++)
    {
        for (int j = 0; j < user_list.size(); j++)
        {
            if (user_list[j].username == completed_vac_app[i].username)
            {
                user_list[j].vaccination_status = vaccinatedStatus;
                if (user_list[j].covid19_status == highRisk)
                    user_list[j].covid19_status = lowRisk;
            }
        }
    }
    write_user_data(user_list);
}

// find the vaccination appoinment with username
vacc_appoinment_data find_vac_app(string username)
{
    vector<vacc_appoinment_data> vac_app_data = read_vaccination_data();
    for (int i = 0; i < vac_app_data.size(); i++)
    {
        if (vac_app_data[i].username == username)
        {
            return vac_app_data[i];
        }
    }
    return {};
}

// get vaccination date which is 2 days from current date
string get_vacc_date(user_data_struct user)
{
    const int TWO_DAYS_IN_SECONDS = 172800;
    time_t current_time = time(0) + TWO_DAYS_IN_SECONDS;
    return parse_date_object(current_time);
}

// display vaccination appoiment
void display_vaccination_app(vacc_appoinment_data user_app)
{
    cout << "\nYour vaccination appoinment\n";
    cout << "\nVaccination Center : " << user_app.vac_center << "\n";
    cout << "\nVaccination Date : " << user_app.vac_date << "\n";
}

// User registering for vaccination
// if the user is vaccinated , user is unable to register for vaccination
// if the user is already registerd , display the vaccination appoinment
// if the user is not yet registered , register the user for vaccination and display the vaccination appoinment
void apply_vaccination(user_data_struct user)
{
    system("cls");
    display_heading("Apply For Vaccination");
    if (user.vaccination_status == vaccinatedStatus)
    {
        cout << "\nYou are already vaccinated\n";
    }
    else
    {
        vacc_appoinment_data user_app = find_vac_app(user.username);
        if (user_app.username != "")
        {
            display_vaccination_app(user_app);
        }
        else
        {
            vector<vac_center_data> vac_center_list = read_vacc_center_data();
            string user_vac_center;
            for (int i = 0; i < vac_center_list.size(); i++)
            {
                if (vac_center_list[i].state == user.state)
                {
                    user_vac_center = vac_center_list[i].vac_center_name;
                    break;
                }
            }
            string user_vac_date = get_vacc_date(user);
            vacc_appoinment_data vac_app;
            vac_app.username = user.username;
            vac_app.vac_center = user_vac_center;
            vac_app.vac_date = user_vac_date;
            bool is_added = add_vaccination_data(vac_app);
            if (is_added)
                display_vaccination_app(vac_app);
            else
                cout << "Failed to add your record. Please try again";
        }
    }
}

//////////////////////////////////////////////////////////// ADMIN

// prompt use whether user wants to register or login

// checking whether username is in the admin list
bool has_username_in_admin_list(string username)
{
    for (int i = 0; i < admin_list.size(); i++)
    {
        if (admin_list[i] == username)
        {
            return true;
        }
    }
    return false;
}

// getting covid-19 positive patients

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

// Admin menu where admin able to perform their functions
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
    {
        return;
    }
    system("pause");
    admin_menu();
}

vector<user_data_struct> get_covid_19_positive(vector<user_data_struct> user_list)
{
    vector<user_data_struct> positive_patients;
    for (int i = 0; i < user_list.size(); i++)
    {
        if (user_list[i].covid19_status == 0)
        {
            positive_patients.push_back(user_list[i]);
        }
    }
    return positive_patients;
}

// view covid-19 positive patients
void view_covid19_positive(void)
{
    system("cls");
    system("Color 0A");
    display_heading("View Covid 19 Positive Patients");
    vector<user_data_struct> user_list = read_user_data();
    vector<user_data_struct> positive_patients = get_covid_19_positive(user_list);
    cout << "\n"
         << left << setw(30) << "Name" << setw(20) << "State\n";
    cout << "\n";
    for (int i = 0; i < positive_patients.size(); i++)
    {
        cout << left << setw(30) << positive_patients[i].fullname << setw(20) << state_list[positive_patients[i].state - 1] << "\n";
    }
}

// get covid 19 positive patients according to the states
// sort the states by number of positive patients
vector<covid_19_stats> get_positive_stats(vector<user_data_struct> user_list)
{
    vector<covid_19_stats> positive_patient_stats;
    for (int i = 0; i < 14; i++)
    {
        covid_19_stats state;
        state.state = i;
        state.quantity = 0;
        positive_patient_stats.push_back(state);
    }
    for (int i = 0; i < user_list.size(); i++)
    {
        if (user_list[i].covid19_status == 0)
        {
            (positive_patient_stats[user_list[i].state - 1].quantity)++;
        }
    }
    quick_sort(positive_patient_stats, 0, (int)positive_patient_stats.size() - 1);
    return positive_patient_stats;
}
// get unvaccinated patients according to the states
// sort the states by number of unvaccinated patients
vector<covid_19_stats> get_unvac_stats(vector<user_data_struct> user_list)
{
    vector<covid_19_stats> unvac_patients;

    for (int i = 0; i < 14; i++)
    {
        covid_19_stats state;
        state.state = i;
        state.quantity = 0;
        unvac_patients.push_back(state);
    }
    for (int i = 0; i <= user_list.size() - 1; i++)
    {
        if (user_list[i].vaccination_status == "B")
        {
            (unvac_patients[user_list[i].state - 1].quantity)++;
        }
    }
    quick_sort(unvac_patients, 0, (int)unvac_patients.size() - 1);
    return unvac_patients;
}

// view covid-19 stats 1.Statistics of Positive patients 2.Statistics of Unvaccinated Patients
void view_covid19_stats(void)
{
    system("cls");
    display_heading("View Covid-19 Statistics");
    vector<user_data_struct> user_list = read_user_data();
    vector<string> options = {"View Covid-19 Positive Patients", "View Unvaccinated Patients"};
    int admin_option;
    display_option(options);
    cout << "\nEnter your option : ";
    cin >> admin_option;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
    }
    while (admin_option < 1 || admin_option > options.size())
    {
        cout << "\nInvalid option\n";
        cout << "\nEnter your option : \n";
        cin >> admin_option;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
    }
    vector<covid_19_stats> stats;
    if (admin_option == 1)
    {
        stats = get_positive_stats(user_list);
    }
    else if (admin_option == 2)
    {
        stats = get_unvac_stats(user_list);
    }
    string option_type;
    if (admin_option == 1)
    {
        option_type = "Covid-19 Patients";
    }
    else
    {
        option_type = "Unvaccinated Users";
    }
    cout << "\n";
    system("cls");
    display_heading(option_type);
    cout << "\n"
         << left << setw(30) << "State" << setw(20) << "Number of " + option_type << "\n\n";

    for (int i = (int)stats.size() - 1; i >= 0; i--)
    {
        cout << left << setw(30) << state_list[stats[i].state] << setw(20) << stats[i].quantity << "\n";
    }
}

// View all the vaccination centers
void view_vaccination_center(void)
{
    system("cls");
    display_heading("View Vaccination Center");
    vector<vac_center_data> vac_center_list = read_vacc_center_data();
    cout << left << setw(20) << "State" << setw(20) << "Vaccination Center\n";
    for (int i = 0; i < vac_center_list.size(); i++)
    {
        cout << left << setw(30) << state_list[vac_center_list[i].state - 1] << setw(20) << vac_center_list[i].vac_center_name << "\n";
    }
    system("pause");
    admin_menu();
}

// View all the vaccination appoinment
void view_vaccination_appoinment(void)
{
    system("cls");
    display_heading("View Vaccination Appoinment");
    vector<vacc_appoinment_data> vac_app_list = read_vaccination_data();
    bool has_vac_app = vac_app_list.size() > 0;
    if (vac_app_list.size() > 0)
    {

        cout << left << setw(20) << "Username" << setw(20) << "Vaccination Center" << setw(20) << "Vaccination Date\n";
        for (int i = 0; i < vac_app_list.size(); i++)
        {
            cout << left << setw(20) << vac_app_list[i].username << setw(20) << vac_app_list[i].vac_center << setw(20) << vac_app_list[i].vac_date << "\n";
        }
    }
    else
        cout << "\nThere is no vaccination appoinments\n";
    system("pause");
    admin_menu();
}