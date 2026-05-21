// Problem 46: Print all prime factors of the given number
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

vector<int> primeFactors(int number) {
    vector<int> result;
    for (int divisor = 2; divisor * divisor <= number; divisor++) {
        while (number % divisor == 0) {
            result.push_back(divisor);
            number /= divisor;
        }
    }
    if (number > 1) result.push_back(number);
    return result;
}

int main() {
    int number;
    cin >> number;
    for (int value : primeFactors(number)) cout << value << ' ';
    cout << '\n';
    return 0;
}
