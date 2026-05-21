// Problem 95: Count number of words in a given string
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
    stringstream stream(text);
    string word;
    int count = 0;
    while (stream >> word) count++;
    cout << count << '\n';
    return 0;
}
