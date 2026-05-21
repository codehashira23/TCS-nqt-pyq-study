// Problem 45: Factors of a given number
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

vector<int> factors(int number) {
    vector<int> result;
    for (int divisor = 1; divisor * divisor <= number; divisor++) {
        if (number % divisor == 0) {
            result.push_back(divisor);
            if (divisor != number / divisor) result.push_back(number / divisor);
        }
    }
    sort(result.begin(), result.end());
    return result;
}

int main() {
    int number;
    cin >> number;
    for (int value : factors(number)) cout << value << ' ';
    cout << '\n';
    return 0;
}
