// Problem 26: Check if a number is palindrome or not
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

bool isPalindromeNumber(long long number) {
    if (number < 0) return false;
    long long original = number;
    long long reversed = 0;
    while (number > 0) {
        reversed = reversed * 10 + number % 10;
        number /= 10;
    }
    return original == reversed;
}

int main() {
    long long number;
    cin >> number;
    cout << (isPalindromeNumber(number) ? "Yes" : "No") << '\n';
    return 0;
}
