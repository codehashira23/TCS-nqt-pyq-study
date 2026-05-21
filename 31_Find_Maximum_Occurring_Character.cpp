/*
   TCS NQT PYQ 31: Find Maximum Occurring Character
   Source: Practice
   Difficulty: Easy
   Topics: String

   QUESTION
   Given a string, find the character that appears most frequently. If there is a tie, print the lexicographically smallest character.

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

int main(){string s; getline(cin,s); map<char,int> f; for(char c:s) if(!isspace((unsigned char)c)) f[c]++; char ans=0; int best=-1; for(auto &p:f) if(p.second>best){best=p.second; ans=p.first;} cout<<ans<<"\n";}
