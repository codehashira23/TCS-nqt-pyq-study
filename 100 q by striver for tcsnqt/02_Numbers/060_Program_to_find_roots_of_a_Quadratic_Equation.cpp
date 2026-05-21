// Problem 60: Program to find roots of a Quadratic Equation
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
    double a, b, c;
    cin >> a >> b >> c;

    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << fixed << setprecision(2) << root1 << ' ' << root2 << '\n';
    } else if (discriminant == 0) {
        double root = -b / (2 * a);
        cout << fixed << setprecision(2) << root << '\n';
    } else {
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-discriminant) / (2 * a);
        cout << fixed << setprecision(2)
             << realPart << " + " << imaginaryPart << "i\n"
             << realPart << " - " << imaginaryPart << "i\n";
    }
    return 0;
}
