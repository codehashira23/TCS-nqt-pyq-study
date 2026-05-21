// Problem 30: Check if a number is armstrong number of not
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

bool isArmstrong(int number) {
    int original = number;
    int digits = to_string(abs(number)).size();
    int sum = 0;

    while (number > 0) {
        int digit = number % 10;
        sum += (int)pow(digit, digits);
        number /= 10;
    }
    return sum == original;
}

int main() {
    int number;
    cin >> number;
    cout << (isArmstrong(number) ? "Yes" : "No") << '\n';
    return 0;
}
