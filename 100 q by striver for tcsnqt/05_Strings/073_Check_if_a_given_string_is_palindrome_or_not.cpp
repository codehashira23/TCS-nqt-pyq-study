// Problem 73: Check if a given string is palindrome or not
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

bool isPalindrome(const string& text) {
    int left = 0, right = (int)text.size() - 1;
    while (left < right) {
        if (text[left] != text[right]) return false;
        left++;
        right--;
    }
    return true;
}

int main() {
    string text;
    getline(cin, text);
    cout << (isPalindrome(text) ? "Yes" : "No") << '\n';
    return 0;
}
