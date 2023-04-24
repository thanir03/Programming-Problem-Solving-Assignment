#include <string>
using namespace std;

// Function Prototype

string decrypt(string str, int key);
string encrypt(string str, int key);

// Decrypt string with a key
string decrypt(string str, int key)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] -= key;
    }
    return str;
}

// Encrypt string with a key
string encrypt(string str, int key)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] += key;
    }
    return str;
}
