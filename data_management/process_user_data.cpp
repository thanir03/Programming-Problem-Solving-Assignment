#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#pragma once
#include "../helper/date_helper.cpp"
#include "../helper/encryption.cpp"
#include "../type.cpp"
#define encryption_key 3
#define splitter '|'
#define user_file "data/users.txt"
using namespace std;

// Function prototype

user_data_struct process_single_user_data(string line);
vector<user_data_struct> read_user_data(void);
void write_user_data(vector<user_data_struct> user_data);
bool add_user_data(user_data_struct new_user);

// Imported Functions

string decrypt(string str, int key);
string encrypt(string str, int key);

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
    user_data_struct single_user_data = {
        username : vectorData[0],
        password : decrypt(vectorData[1], encryption_key),
        phone_num : vectorData[2],
        ic : vectorData[3],
        fullname : vectorData[4],
        dob : vectorData[5],
        address : vectorData[6],
        postcode : vectorData[7],
        state : stoi(vectorData[8]),
        vaccination_status : vectorData[9],
        covid19_status : stoi(vectorData[10]),
        dependant : vectorData[11],
        dependant_relationship : vectorData[12],
    };
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
