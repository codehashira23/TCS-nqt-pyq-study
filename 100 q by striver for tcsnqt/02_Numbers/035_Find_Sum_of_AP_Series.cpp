// Problem 35: Find Sum of AP Series
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

double sumOfAP(double firstTerm, double commonDifference, int terms) {
    return terms / 2.0 * (2 * firstTerm + (terms - 1) * commonDifference);
}

int main() {
    double firstTerm, commonDifference;
    int terms;
    cin >> firstTerm >> commonDifference >> terms;
    cout << fixed << setprecision(2) << sumOfAP(firstTerm, commonDifference, terms) << '\n';
    return 0;
}
