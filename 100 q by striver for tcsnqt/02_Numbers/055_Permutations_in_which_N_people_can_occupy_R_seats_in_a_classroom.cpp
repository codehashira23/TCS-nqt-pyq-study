// Problem 55: Permutations in which N people can occupy R seats in a classroom
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

long long permutations(int people, int seats) {
    if (seats > people) return 0;
    long long result = 1;
    for (int i = 0; i < seats; i++) {
        result *= (people - i);
    }
    return result;
}

int main() {
    int people, seats;
    cin >> people >> seats;
    cout << permutations(people, seats) << '\n';
    return 0;
}
