// Problem 97: Change case of each character in a string
// Topic: 05 Strings
//
// How to study this file:
// - Read the top comments first to understand the idea.
// - Then read the function, because the function is the reusable solution.
// - Finally read main(), which shows a simple input-output format.
//
// All code uses C++17 and avoids shortcuts so that the logic is easy to revise.

#include <bits/stdc++.h>
using namespace std;

int main() {
    string text;
    getline(cin, text);
    for (char& ch : text) {
        if (islower((unsigned char)ch)) ch = toupper(ch);
        else if (isupper((unsigned char)ch)) ch = tolower(ch);
    }
    cout << text << '\n';
    return 0;
}
