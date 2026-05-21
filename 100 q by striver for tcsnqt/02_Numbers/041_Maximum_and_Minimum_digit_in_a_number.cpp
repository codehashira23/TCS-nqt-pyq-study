// Problem 41: Maximum and Minimum digit in a number
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

pair<int, int> minMaxDigit(long long number) {
    number = llabs(number);
    if (number == 0) return {0, 0};

    int minimumDigit = 9;
    int maximumDigit = 0;
    while (number > 0) {
        int digit = number % 10;
        minimumDigit = min(minimumDigit, digit);
        maximumDigit = max(maximumDigit, digit);
        number /= 10;
    }
    return {minimumDigit, maximumDigit};
}

int main() {
    long long number;
    cin >> number;
    auto answer = minMaxDigit(number);
    cout << "Minimum: " << answer.first << '\n';
    cout << "Maximum: " << answer.second << '\n';
    return 0;
}
