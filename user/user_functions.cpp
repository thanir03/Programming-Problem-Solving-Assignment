#pragma once
#include "./user_helper.cpp"
#include "./user_menu.cpp"
#include "./user_register.cpp"
using namespace std;
void user_menu(string username);

void view_user_profile(user_data_struct user);
void update_profile(user_data_struct user);
void update_medical_history(user_data_struct user);
vector<string> notification(string username);

vector<string> notification(string username)
{
    vector<user_data_struct> user_list = read_user_data();
    user_data_struct user = has_username_in_db(user_list, username);
    vector<string> actions = {};
    if (user.covid19_status == 0)
    {
        actions.push_back("Quarantine for 10 days");
        actions.push_back("Perform a Covid 19 Test after 10 days");
    }
    else if (user.covid19_status == 1)
    {
        actions.push_back("Perform a Covid 19 Test immediately");
        actions.push_back("Quarantine for 3 days");
    }
    else if (user.covid19_status == 2)
    {
        actions.push_back("Apply for vaccination");
    }
    else
    {
        if (user.dependant != "0")
        {
            user_data_struct dependant = has_username_in_db(user_list, user.dependant);

            if (dependant.covid19_status == 0 && user.covid19_status != 1 && user.covid19_status != 0)
            {
                for (int i = 0; i < user_list.size(); i++)
                {
                    if (user_list[i].username == username)
                    {
                        user_list[i].covid19_status = 1;
                    }
                }
                write_user_data(user_list);
                actions.push_back("Quarantine for 10 days");
                actions.push_back("Perform a Covid 19 Test immediately");
            }
        }
    }
    return actions;
}

bool validate_test_date(string date)
{
    if (date.length() != 10)
    {
        return false;
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    int current_year = 1970 + (time(NULL) / 60 / 60 / 24 / 365);
    cout << day << month << year;
    if (day > 31 || day < 0 || month < 0 || month > 12 || year != current_year)
    {
        return false;
    }
    return true;
}

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

            cout << "\n"
                 << "Invalid Date"
                 << "\n";
            cout << "When was the COVID 19 test taken ? ";
            getline(cin, covid_19_test_date);
        }

        cout << "\nP - Positive\n";
        cout << "\nN - Negative\n";
        cout << "\nWhat is the outcome of the test ? (P/N)";
        cin >> covid19_test_result;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            covid19_test_result = 'A';
        }
        while (toupper(covid19_test_result) != 'P' && toupper(covid19_test_result) != 'N')
        {
            cout << "\nWhat is the outcome of the test ? ";
            cin >> covid19_test_result;
        }
        if (covid19_test_result == 'P')
        {
            covid19_status = 0;
        }
        else
        {
            covid19_status = ((user.vaccination_status == "A") ? 3 : 2);
        }
        cout << "\nThank you for updating your covid19 test.\n";
        user.covid19_test_result = covid19_test_result;
        user.covid_19_test_date = covid_19_test_date;
        user.covid19_status = covid19_status;
        change_single_user_data(user);
        system("pause");
        user_menu(user.username);
    }
}

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

void update_profile(user_data_struct user)
{
    vector<user_data_struct> user_list = read_user_data();
    display_heading("UPDATE PROFILE");
    display_option({"Phone Number", "Address", "Postcode", "Dependant", "State"});
    int user_option;
    cout << "Enter your option : ";
    cin >> user_option;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
    }
    while (user_option < 1 && user_option > 5)
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
    }
    change_single_user_data(user);
    system("pause");
    cout << "User details updated successfully";
    user_menu(user.username);
}

void update_user_data(void)
{
}

void apply_vaccination(user_data_struct user)
{
    display_heading("Apply For Vaccination");
    if (user.vaccination_status == "A")
    {
        cout << "You are already vaccinated";
        return;
    }
    system("pause");
    user_menu(user.username);
}
