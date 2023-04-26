#include <vector>
#include <string>
#include "../data_management/process_user_data.h"
#include "../type.h"
using namespace std;

// Function prototype
user_data_struct has_username_in_db(vector<user_data_struct> data, string username);
void change_single_user_data(user_data_struct user);

// finding the user with the given user vector
user_data_struct has_username_in_db(vector<user_data_struct> data, string username)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].username == username)
        {
            return data[i];
        }
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
