// Problem 28: Check if a number is prime or not
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

bool isPrime(long long number) {
    if (number <= 1) return false;
    if (number <= 3) return true;
    if (number % 2 == 0 || number % 3 == 0) return false;

    for (long long divisor = 5; divisor * divisor <= number; divisor += 6) {
        if (number % divisor == 0 || number % (divisor + 2) == 0) return false;
    }
    return true;
}

int main() {
    long long number;
    cin >> number;
    cout << (isPrime(number) ? "Prime" : "Not Prime") << '\n';
    return 0;
}
