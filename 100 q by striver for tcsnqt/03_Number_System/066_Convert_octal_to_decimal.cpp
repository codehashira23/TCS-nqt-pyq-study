// Problem 66: Convert octal to decimal
// Topic: 03 Number System
//
// How to study this file:
// - Read the top comments first to understand the idea.
// - Then read the function, because the function is the reusable solution.
// - Finally read main(), which shows a simple input-output format.
//
// All code uses C++17 and avoids shortcuts so that the logic is easy to revise.

#include <bits/stdc++.h>
using namespace std;

long long octalToDecimal(string octal) {
    long long decimal = 0;
    for (char digit : octal) {
        decimal = decimal * 8 + (digit - '0');
    }
    return decimal;
}

int main() {
    string octal;
    cin >> octal;
    cout << octalToDecimal(octal) << '\n';
    return 0;
}
