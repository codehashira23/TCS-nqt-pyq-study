// Problem 56: Program to add two fractions
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

pair<long long, long long> addFractions(long long n1, long long d1, long long n2, long long d2) {
    long long numerator = n1 * d2 + n2 * d1;
    long long denominator = d1 * d2;
    long long divisor = gcdEuclid(numerator, denominator);
    return {numerator / divisor, denominator / divisor};
}

int main() {
    long long n1, d1, n2, d2;
    cin >> n1 >> d1 >> n2 >> d2;
    auto answer = addFractions(n1, d1, n2, d2);
    cout << answer.first << '/' << answer.second << '\n';
    return 0;
}
