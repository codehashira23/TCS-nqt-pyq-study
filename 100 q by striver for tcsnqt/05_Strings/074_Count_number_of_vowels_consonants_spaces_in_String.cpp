// Problem 74: Count number of vowels, consonants, spaces in String
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

bool isVowel(char ch) {
    ch = tolower(ch);
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

int main() {
    string text;
    getline(cin, text);
    int vowels = 0, consonants = 0, spaces = 0;

    for (char ch : text) {
        if (ch == ' ') spaces++;
        else if (isalpha(ch) && isVowel(ch)) vowels++;
        else if (isalpha(ch)) consonants++;
    }

    cout << "Vowels: " << vowels << '\n';
    cout << "Consonants: " << consonants << '\n';
    cout << "Spaces: " << spaces << '\n';
    return 0;
}
