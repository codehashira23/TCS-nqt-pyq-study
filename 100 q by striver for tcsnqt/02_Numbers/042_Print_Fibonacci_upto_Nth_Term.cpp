// Problem 42: Print Fibonacci upto Nth Term
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

vector<long long> fibonacciTerms(int n) {
    vector<long long> result;
    long long first = 0, second = 1;
    for (int i = 1; i <= n; i++) {
        result.push_back(first);
        long long next = first + second;
        first = second;
        second = next;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    for (long long value : fibonacciTerms(n)) cout << value << ' ';
    cout << '\n';
    return 0;
}
