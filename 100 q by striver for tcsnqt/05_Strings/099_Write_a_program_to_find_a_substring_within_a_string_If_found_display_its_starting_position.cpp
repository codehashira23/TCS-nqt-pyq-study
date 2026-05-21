// Problem 99: Write a program to find a substring within a string. If found display its starting position
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
    string text, pattern;
    getline(cin, text);
    getline(cin, pattern);
    size_t position = text.find(pattern);
    if (position == string::npos) cout << -1 << '\n';
    else cout << position << '\n';
    return 0;
}
