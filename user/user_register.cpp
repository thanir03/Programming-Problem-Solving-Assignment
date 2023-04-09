#pragma once
#include "../data_management/process_user_data.cpp"
#include "./user_helper.cpp"

void user_register(void);

bool validateState(int state)
{
    if (state < 1 || state > 14)
        return false;
    return true;
}

bool validate_username(string word)
{
    if (word.length() < 5)
        return false;
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == ' ')
        {
            return false;
        }
    }
    return true;
}

bool validateIdentityNumber(string ic)
{
    if (ic.length() != 12)
        return false;
    if (stoi(ic.substr(0, 2)))
        for (int i = 0; i < ic.length(); i++)
        {
            if (!isdigit(ic[i]))
                return false;
        }
    return true;
}

string extract_dob_from_ic(string ic)
{
    string year, date, month;
    string dob_from_ic = ic.substr(0, 6);
    if (stoi(dob_from_ic.substr(0, 1)) <= 2)
    {
        year = "20" + dob_from_ic.substr(0, 2);
    }
    else
    {
        year = "19" + dob_from_ic.substr(0, 2);
    }
    month = dob_from_ic.substr(2, 2);
    date = dob_from_ic.substr(4, 2);
    return date + "/" + month + "/" + year;
}

bool validateName(string name)
{
    for (int i = 0; i < name.length(); i++)
    {
        if (!isalpha(name[i]))
            return false;
    }
    return true;
}

bool validatePostcode(string postcode)
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

bool validateAddress(string address)
{
    return address.length() > 10;
}

bool validatePhoneNum(string phone_num)
{
    cout << phone_num;
    if (phone_num.length() < 10)
    {
        cout << "length";
        return false;
    }
    for (int i = 0; i < phone_num.length(); i++)
    {
        if (!isdigit(phone_num[i]))
        {
            cout << "digit";
            return false;
        }
    }
    return true;
}

string read_username(vector<user_data_struct> data)
{
    string username;
    cout << "\nExample : cristian7 \n";
    cout << "Enter an unique username : ";
    cin.ignore();
    getline(cin, username);
    while (has_username_in_db(data, username).username != "" && username != "" && !validate_username(username))
    {
        cout << username;
        cout << "\nUsername exist in database or Invalid Username\n";
        cout << "Enter an unique username : ";
        getline(cin, username);
    }
    return username;
}

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

string read_phone_num(void)
{
    string phone_num;
    cout << "\nExample : 0194798675\n";
    cout << "Enter your phone number : ";
    getline(cin, phone_num);
    while (!validatePhoneNum(phone_num))
    {
        cout << "\nPhone Number invalid\n";
        cout << "Enter your phone number : ";
        getline(cin, phone_num);
    }
    return phone_num;
}

string read_ic(void)
{
    string ic;
    cout << "\nExample : 0XXXXXXXXXXX\n";
    cout << "Enter your IC number : ";
    getline(cin, ic);
    while (!validateIdentityNumber(ic))
    {
        cout << ic;
        cout << "\nIC invalid\n";
        cout << "Enter your IC number : ";
        getline(cin, ic);
    }
    return ic;
}

string read_fullname(void)
{
    string fullname;
    cout << "\nExample : Thanirmalai Nagappan\n";
    cout << "Enter your Full name: ";
    getline(cin, fullname);
    while (validateName(fullname))
    {
        cout << "\nInvalid name\n";
        cout << "Enter your Full name ";
        getline(cin, fullname);
    }
    return fullname;
}

string read_address(void)
{
    string address;
    cout << "\nExample : 41-1 Persiaran Lemak Taman Segar\n";
    cout << "Enter your address: ";
    getline(cin, address);
    while (!validateAddress(address))
    {
        cout << "\nInvalid address\n";
        cout << "Enter your address: ";
        getline(cin, address);
    }
    return address;
}

string read_postcode(void)
{
    string postcode;
    cout << "\nExample : 56100\n";
    cout << "Enter your postcode : ";
    getline(cin, postcode);
    while (!validatePostcode(postcode))
    {
        cout << "\nInvalid postcode\n";
        cout << "Enter your postcode : ";
        getline(cin, postcode);
    }
    return postcode;
}

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
    while (!validateState(state))
    {
        cout << "\nInvalid state\n";
        cout << "Enter your state : ";
        cin >> state;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            state = -1;
            cout << "run failure";
        }
    }
    return state;
}

void read_dependant(string *dependant, string *dependant_relationship, vector<user_data_struct> data)
{
    cout << "\nExample : cristiano7\n";
    cout << "Enter dependant username : ";
    getline(cin, *dependant);
    while (has_username_in_db(data, *dependant).username == "")
    {
        cout << "\n Username doesnt exist in database\n";
        cout << "Enter dependant username : ";
        getline(cin, *dependant);
    }
    cout << "Enter dependant relationship : ";
    getline(cin, *dependant_relationship);
}

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
    new_user_data.covid19_test_result = '0';
    new_user_data.covid_19_test_date = '0';
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
