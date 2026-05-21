// Problem 44: Power of a number
// Topic: 02 Numbers
//
// How to study this file:
// - Read the top comments first to understand the idea.
// - Then read the function, because the function is the reusable solution.
// - Finally read main(), which shows a simple input-output format.
//
// All code uses C++17 and avoids shortcuts so that the logic is easy to revise.

#include <bits/stdc++.h>
using namespace std;

long long fastPower(long long base, long long exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) result *= base;
        base *= base;
        exponent /= 2;
    }
    return result;
}

int main() {
    long long base, exponent;
    cin >> base >> exponent;
    cout << fastPower(base, exponent) << '\n';
    return 0;
}
