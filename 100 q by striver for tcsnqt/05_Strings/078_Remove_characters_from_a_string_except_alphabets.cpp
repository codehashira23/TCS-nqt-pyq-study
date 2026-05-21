// Problem 78: Remove characters from a string except alphabets
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
    string result;
    for (char ch : text) {
        if (isalpha((unsigned char)ch)) result.push_back(ch);
    }
    cout << result << '\n';
    return 0;
}
