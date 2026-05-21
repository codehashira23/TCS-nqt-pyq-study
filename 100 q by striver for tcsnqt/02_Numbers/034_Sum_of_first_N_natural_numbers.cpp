// Problem 34: Sum of first N natural numbers
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

long long sumOfNaturalNumbers(long long n) {
    return n * (n + 1) / 2;
}

int main() {
    long long n;
    cin >> n;
    cout << sumOfNaturalNumbers(n) << '\n';
    return 0;
}
