/*
   TCS NQT PYQ 48: Reverse a String Without Built-In Functions
   Source: Verified PYQ
   Difficulty: Easy
   Topics: String

   QUESTION
   Reverse a given string without using any built-in reverse methods or slicing.

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

int main(){string s; getline(cin,s); for(int l=0,r=(int)s.size()-1;l<r;l++,r--) swap(s[l],s[r]); cout<<s<<"\n";}
