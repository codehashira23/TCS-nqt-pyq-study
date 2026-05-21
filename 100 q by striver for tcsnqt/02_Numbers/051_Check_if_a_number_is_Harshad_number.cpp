// Problem 51: Check if a number is Harshad number
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

bool isHarshad(int number) {
    int original = number;
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum != 0 && original % sum == 0;
}

int main() {
    int number;
    cin >> number;
    cout << (isHarshad(number) ? "Yes" : "No") << '\n';
    return 0;
}
