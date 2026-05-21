// Problem 36: Program to find sum of GP Series
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

double sumOfGP(double firstTerm, double commonRatio, int terms) {
    if (terms == 0) return 0;
    if (commonRatio == 1) return firstTerm * terms;
    return firstTerm * (pow(commonRatio, terms) - 1) / (commonRatio - 1);
}

int main() {
    double firstTerm, commonRatio;
    int terms;
    cin >> firstTerm >> commonRatio >> terms;
    cout << fixed << setprecision(2) << sumOfGP(firstTerm, commonRatio, terms) << '\n';
    return 0;
}
