// Problem 33: Check weather a given number is positive or negative
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

int main() {
    long long number;
    cin >> number;
    if (number > 0) cout << "Positive\n";
    else if (number < 0) cout << "Negative\n";
    else cout << "Zero\n";
    return 0;
}
