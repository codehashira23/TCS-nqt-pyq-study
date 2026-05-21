// Problem 43: Factorial of a number
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

long long factorial(int n) {
    long long result = 1;
    for (int number = 2; number <= n; number++) {
        result *= number;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    cout << factorial(n) << '\n';
    return 0;
}
