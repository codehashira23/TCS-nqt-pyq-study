// Problem 52: Check if the number is abundant number or not
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

bool isAbundant(int number) {
    if (number <= 1) return false;
    int divisorSum = 1;
    for (int divisor = 2; divisor * divisor <= number; divisor++) {
        if (number % divisor == 0) {
            divisorSum += divisor;
            if (divisor != number / divisor) divisorSum += number / divisor;
        }
    }
    return divisorSum > number;
}

int main() {
    int number;
    cin >> number;
    cout << (isAbundant(number) ? "Yes" : "No") << '\n';
    return 0;
}
