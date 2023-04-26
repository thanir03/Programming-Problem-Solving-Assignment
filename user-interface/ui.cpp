#include <iostream>
#include <string>
#include <vector>
// Imported files
#include "../type.h"
using namespace std;
// done

// Function prototype
void display_heading(string title);
void display_option(vector<string> options);

// Display heading of the program
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