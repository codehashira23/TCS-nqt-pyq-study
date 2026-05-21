// Problem 29: Prime numbers in a given range
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

vector<int> sievePrimes(int limit) {
    vector<bool> isPrime(limit + 1, true);
    if (limit >= 0) isPrime[0] = false;
    if (limit >= 1) isPrime[1] = false;

    for (int number = 2; number * number <= limit; number++) {
        if (isPrime[number]) {
            for (int multiple = number * number; multiple <= limit; multiple += number) {
                isPrime[multiple] = false;
            }
        }
    }

    vector<int> primes;
    for (int number = 2; number <= limit; number++) {
        if (isPrime[number]) primes.push_back(number);
    }
    return primes;
}

int main() {
    int left, right;
    cin >> left >> right;
    for (int prime : sievePrimes(right)) {
        if (prime >= left) cout << prime << ' ';
    }
    cout << '\n';
    return 0;
}
