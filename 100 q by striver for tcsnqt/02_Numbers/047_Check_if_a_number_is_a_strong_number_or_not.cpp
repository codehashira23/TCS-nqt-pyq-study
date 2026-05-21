// Problem 47: Check if a number is a strong number or not
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

bool isStrongNumber(int number) {
    vector<int> factorial(10, 1);
    for (int digit = 1; digit <= 9; digit++) {
        factorial[digit] = factorial[digit - 1] * digit;
    }

    int original = number;
    int sum = 0;
    if (number == 0) sum = 1;
    while (number > 0) {
        sum += factorial[number % 10];
        number /= 10;
    }
    return sum == original;
}

int main() {
    int number;
    cin >> number;
    cout << (isStrongNumber(number) ? "Yes" : "No") << '\n';
    return 0;
}
