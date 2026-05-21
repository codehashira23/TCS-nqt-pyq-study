/*
   TCS NQT PYQ 43: Distinct Bitwise OR of Subarrays
   Source: Verified PYQ
   Exam/Shift: 29 April 2024 Kolkata Q2
   Difficulty: Hard
   Topics: Bit Manipulation, Array

   QUESTION
   Given an integer array, find the number of distinct values that can be obtained as the bitwise OR of any contiguous subarray.

   CONSTRAINTS
   - 1 <= N <= 1000 for DP/backtracking style inputs; use modulo where asked.
   - Input is assumed valid unless the problem explicitly asks for validation.
   - Use O(N) or better whenever a direct traversal solution exists.

   INPUT FORMAT
   N followed by N array elements. Extra values such as K/S are read after the array when needed.

   OUTPUT FORMAT
   The answer required by the question.

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

int main(){int n; cin>>n; unordered_set<int> all,prev,cur; for(int i=0,x;i<n;i++){cin>>x; cur.clear(); cur.insert(x); for(int v:prev) cur.insert(v|x); for(int v:cur) all.insert(v); prev=cur;} cout<<all.size()<<"\n";}
