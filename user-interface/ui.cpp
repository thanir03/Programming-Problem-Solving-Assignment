#pragma once
using namespace std;

void display_heading(string title)
{
    cout << "\t=================================================================\n";
    cout << "\t" << title << "\n";
    cout << "\t=================================================================\n\n";
}
void display_option(vector<string> options)
{
    for (int i = 0; i < options.size(); i++)
    {
        cout << "<" << i + 1 << "> " << options[i] << "\n";
    }
}