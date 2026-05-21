// Problem 62: Convert binary to octal
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

string binaryToOctal(string binary) {
    while (binary.size() % 3 != 0) binary = '0' + binary;
    string octal;
    for (int i = 0; i < (int)binary.size(); i += 3) {
        int value = (binary[i] - '0') * 4 + (binary[i + 1] - '0') * 2 + (binary[i + 2] - '0');
        octal.push_back(char('0' + value));
    }
    int firstNonZero = octal.find_first_not_of('0');
    return firstNonZero == string::npos ? "0" : octal.substr(firstNonZero);
}

int main() {
    string binary;
    cin >> binary;
    cout << binaryToOctal(binary) << '\n';
    return 0;
}
