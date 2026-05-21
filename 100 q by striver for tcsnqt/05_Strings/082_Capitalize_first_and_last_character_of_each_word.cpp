// Problem 82: Capitalize first and last character of each word
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

string capitalizeFirstLast(string text) {
    int n = text.size();
    for (int i = 0; i < n; i++) {
        if (isalpha((unsigned char)text[i])) {
            int start = i;
            while (i < n && isalpha((unsigned char)text[i])) i++;
            int end = i - 1;
            text[start] = toupper(text[start]);
            text[end] = toupper(text[end]);
        }
    }
    return text;
}

int main() {
    string text;
    getline(cin, text);
    cout << capitalizeFirstLast(text) << '\n';
    return 0;
}
