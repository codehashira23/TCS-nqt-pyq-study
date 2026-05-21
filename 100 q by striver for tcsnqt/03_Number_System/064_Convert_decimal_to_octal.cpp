// Problem 64: Convert decimal to octal
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

string decimalToOctal(long long number) {
    if (number == 0) return "0";
    string octal;
    while (number > 0) {
        octal.push_back(char('0' + number % 8));
        number /= 8;
    }
    reverse(octal.begin(), octal.end());
    return octal;
}

int main() {
    long long number;
    cin >> number;
    cout << decimalToOctal(number) << '\n';
    return 0;
}
