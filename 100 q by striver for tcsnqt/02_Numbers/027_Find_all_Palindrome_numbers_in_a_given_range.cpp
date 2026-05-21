// Problem 27: Find all Palindrome numbers in a given range
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

bool isPalindrome(int number) {
    int original = number, reversed = 0;
    while (number > 0) {
        reversed = reversed * 10 + number % 10;
        number /= 10;
    }
    return original == reversed;
}

int main() {
    int left, right;
    cin >> left >> right;
    for (int number = left; number <= right; number++) {
        if (number >= 0 && isPalindrome(number)) cout << number << ' ';
    }
    cout << '\n';
    return 0;
}
