// Problem 48: Check if a Number is Automorphic
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

bool isAutomorphic(long long number) {
    long long square = number * number;
    while (number > 0) {
        if (number % 10 != square % 10) return false;
        number /= 10;
        square /= 10;
    }
    return true;
}

int main() {
    long long number;
    cin >> number;
    cout << (isAutomorphic(number) ? "Yes" : "No") << '\n';
    return 0;
}
