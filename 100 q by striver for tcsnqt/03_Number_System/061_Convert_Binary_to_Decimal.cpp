// Problem 61: Convert Binary to Decimal
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

long long binaryToDecimal(string binary) {
    long long decimal = 0;
    for (char bit : binary) {
        decimal = decimal * 2 + (bit - '0');
    }
    return decimal;
}

int main() {
    string binary;
    cin >> binary;
    cout << binaryToDecimal(binary) << '\n';
    return 0;
}
