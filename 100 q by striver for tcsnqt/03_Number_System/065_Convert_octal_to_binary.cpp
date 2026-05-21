// Problem 65: Convert octal to binary
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

string octalToBinary(string octal) {
    vector<string> table = {"000", "001", "010", "011", "100", "101", "110", "111"};
    string binary;
    for (char digit : octal) binary += table[digit - '0'];
    int firstNonZero = binary.find_first_not_of('0');
    return firstNonZero == string::npos ? "0" : binary.substr(firstNonZero);
}

int main() {
    string octal;
    cin >> octal;
    cout << octalToBinary(octal) << '\n';
    return 0;
}
