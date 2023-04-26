#ifndef USER_REGISTER_H
#define USER_REGISER_H
#include <string>
#include <vector>
#include <iostream>
#include "../type.h"

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

#endif // USER_REGISER_H