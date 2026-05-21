// Problem 58: Can a number be expressed as a sum of two prime numbers
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

bool isPrime(int number) {
    if (number <= 1) return false;
    for (int divisor = 2; divisor * divisor <= number; divisor++) {
        if (number % divisor == 0) return false;
    }
    return true;
}

bool canBePrimeSum(int number) {
    for (int first = 2; first <= number / 2; first++) {
        if (isPrime(first) && isPrime(number - first)) return true;
    }
    return false;
}

int main() {
    int number;
    cin >> number;
    cout << (canBePrimeSum(number) ? "Yes" : "No") << '\n';
    return 0;
}
