// Problem 57: Replace all 0s with 1s in a given integer
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

long long replaceZerosWithOnes(long long number) {
    if (number == 0) return 1;
    long long place = 1;
    long long result = 0;
    while (number > 0) {
        int digit = number % 10;
        if (digit == 0) digit = 1;
        result += digit * place;
        place *= 10;
        number /= 10;
    }
    return result;
}

int main() {
    long long number;
    cin >> number;
    cout << replaceZerosWithOnes(number) << '\n';
    return 0;
}
