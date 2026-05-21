// Problem 40: Reverse digits of a number
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

long long reverseDigits(long long number) {
    long long sign = number < 0 ? -1 : 1;
    number = llabs(number);
    long long reversed = 0;
    while (number > 0) {
        reversed = reversed * 10 + number % 10;
        number /= 10;
    }
    return sign * reversed;
}

int main() {
    long long number;
    cin >> number;
    cout << reverseDigits(number) << '\n';
    return 0;
}
