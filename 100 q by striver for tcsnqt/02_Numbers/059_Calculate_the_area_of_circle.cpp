// Problem 59: Calculate the area of circle
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
    const double pi = acos(-1.0);
    double radius;
    cin >> radius;
    cout << fixed << setprecision(2) << pi * radius * radius << '\n';
    return 0;
}
