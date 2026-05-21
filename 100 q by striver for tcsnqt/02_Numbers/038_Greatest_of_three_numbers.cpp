// Problem 38: Greatest of three numbers
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
    int first, second, third;
    cin >> first >> second >> third;
    cout << max(first, max(second, third)) << '\n';
    return 0;
}
