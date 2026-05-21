/*
   TCS NQT PYQ 36: Longest Common Subsequence (LCS)
   Source: Practice
   Difficulty: Hard
   Topics: Dynamic Programming, String

   QUESTION
   Given two strings, find the length of their Longest Common Subsequence (LCS).

   CONSTRAINTS
   - 1 <= N <= 1000 for DP/backtracking style inputs; use modulo where asked.
   - Input is assumed valid unless the problem explicitly asks for validation.
   - Use O(N) or better whenever a direct traversal solution exists.

   INPUT FORMAT
   The integer values described in the question.

   OUTPUT FORMAT
   The computed answer.

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

int main(){string a,b; cin>>a>>b; vector<int> prev(b.size()+1),cur(b.size()+1); for(char x:a){for(size_t j=1;j<=b.size();j++) cur[j]=(x==b[j-1]?1+prev[j-1]:max(prev[j],cur[j-1])); swap(prev,cur);} cout<<prev[b.size()]<<"\n";}
