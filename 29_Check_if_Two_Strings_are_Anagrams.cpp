/*
   TCS NQT PYQ 29: Check if Two Strings are Anagrams
   Source: Practice
   Difficulty: Easy
   Topics: String

   QUESTION
   Given two strings, check if they are anagrams of each other, meaning both contain the same characters with the same frequencies.

   CONSTRAINTS
   - 1 <= length of string <= 100000.
   - Input is assumed valid unless the problem explicitly asks for validation.
   - Use O(N) or better whenever a direct traversal solution exists.

   INPUT FORMAT
   The string input described in the question.

   OUTPUT FORMAT
   The required string/count/result.

   EXPLANATION
   Read the statement slowly and identify the core operation:
   traversal, hashing, two pointers, dynamic programming, math formula, or graph traversal.
   The implementation below keeps the code short, but the comments above should help you
   revise the problem as a self-study note before coding it again from memory.

   TEACHING NOTE
   1. Write down what one input item means.
   2. Decide which data structure stores only the information needed for the answer.
   3. Dry-run a small custom test before trusting the code.
   4. Check edge cases: minimum N, duplicates, zero values, and negative values where allowed.
*/

#include <bits/stdc++.h>
using namespace std;

int main(){string a,b; getline(cin,a); getline(cin,b); array<int,256> f{}; for(unsigned char c:a) if(!isspace(c)) f[tolower(c)]++; for(unsigned char c:b) if(!isspace(c)) f[tolower(c)]--; cout<<(all_of(f.begin(),f.end(),[](int x){return x==0;})?"Anagram":"Not Anagram")<<"\n";}
