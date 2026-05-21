// Problem 63: Decimal to Binary conversion
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

string decimalToBinary(long long number) {
    if (number == 0) return "0";
    string binary;
    while (number > 0) {
        binary.push_back(char('0' + number % 2));
        number /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

int main() {
    long long number;
    cin >> number;
    cout << decimalToBinary(number) << '\n';
    return 0;
}
