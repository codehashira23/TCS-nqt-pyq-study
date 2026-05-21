// Problem 93: Write a program to find the largest word in a given string.
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
    string word, largest;
    while (stream >> word) {
        if (word.size() > largest.size()) largest = word;
    }
    cout << largest << '\n';
    return 0;
}
