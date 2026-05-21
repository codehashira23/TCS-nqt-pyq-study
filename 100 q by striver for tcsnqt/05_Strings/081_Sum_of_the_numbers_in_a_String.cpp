// Problem 81: Sum of the numbers in a String
// Topic: 05 Strings
//
// How to study this file:
// - Read the top comments first to understand the idea.
// - Then read the function, because the function is the reusable solution.
// - Finally read main(), which shows a simple input-output format.
//
// All code uses C++17 and avoids shortcuts so that the logic is easy to revise.

#include <bits/stdc++.h>
using namespace std;

long long sumNumbersInString(const string& text) {
    long long sum = 0;
    long long currentNumber = 0;
    bool buildingNumber = false;

    for (char ch : text) {
        if (isdigit((unsigned char)ch)) {
            currentNumber = currentNumber * 10 + (ch - '0');
            buildingNumber = true;
        } else if (buildingNumber) {
            sum += currentNumber;
            currentNumber = 0;
            buildingNumber = false;
        }
    }
    if (buildingNumber) sum += currentNumber;
    return sum;
}

int main() {
    string text;
    getline(cin, text);
    cout << sumNumbersInString(text) << '\n';
    return 0;
}
