// Problem 67: Convert digits/numbers to words
// Topic: 03 Number System
//
// How to study this file:
// - Read the top comments first to understand the idea.
// - Then read the function, because the function is the reusable solution.
// - Finally read main(), which shows a simple input-output format.
//
// All code uses C++17 and avoids shortcuts so that the logic is easy to revise.

#include <bits/stdc++.h>
using namespace std;

string digitsToWords(string number) {
    vector<string> words = {"zero", "one", "two", "three", "four",
                            "five", "six", "seven", "eight", "nine"};
    string result;
    for (char digit : number) {
        if (isdigit(digit)) {
            if (!result.empty()) result += ' ';
            result += words[digit - '0'];
        }
    }
    return result;
}

int main() {
    string number;
    cin >> number;
    cout << digitsToWords(number) << '\n';
    return 0;
}
