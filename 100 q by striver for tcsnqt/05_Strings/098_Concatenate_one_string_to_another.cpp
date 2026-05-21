// Problem 98: Concatenate one string to another
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
    string first, second;
    getline(cin, first);
    getline(cin, second);
    cout << first + second << '\n';
    return 0;
}
