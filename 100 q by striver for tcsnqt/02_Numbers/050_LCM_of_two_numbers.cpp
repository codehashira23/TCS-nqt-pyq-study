// Problem 50: LCM of two numbers
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
    while (second != 0) {
        long long remainder = first % second;
        first = second;
        second = remainder;
    }
    return llabs(first);
}

long long lcm(long long first, long long second) {
    if (first == 0 || second == 0) return 0;
    return llabs(first / gcdEuclid(first, second) * second);
}

int main() {
    long long first, second;
    cin >> first >> second;
    cout << lcm(first, second) << '\n';
    return 0;
}
