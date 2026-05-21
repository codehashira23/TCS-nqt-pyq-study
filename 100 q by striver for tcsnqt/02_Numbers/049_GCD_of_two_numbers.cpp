// Problem 49: GCD of two numbers
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

long long gcdEuclid(long long first, long long second) {
    first = llabs(first);
    second = llabs(second);
    while (second != 0) {
        long long remainder = first % second;
        first = second;
        second = remainder;
    }
    return first;
}

int main() {
    long long first, second;
    cin >> first >> second;
    cout << gcdEuclid(first, second) << '\n';
    return 0;
}
