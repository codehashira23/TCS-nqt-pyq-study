/*
   TCS NQT PYQ 71: Sort 0s, 1s and 2s — Dutch National Flag (2026 Pattern)
   Source: Verified PYQ
   Exam/Shift: 2026
   Difficulty: Medium
   Topics: Array, Two Pointers

   QUESTION
   Given an array of N integers consisting only of 0s, 1s, and 2s, sort it in a single traversal without using any built-in sort. All 0s should come first, followed by 1s, then 2s.

   CONSTRAINTS
   - 1 <= N <= 100000 unless the statement says a smaller limit.
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

int main(){int n; cin>>n; vector<int>a(n); for(int &x:a) cin>>x; int l=0,m=0,h=n-1; while(m<=h){if(a[m]==0) swap(a[l++],a[m++]); else if(a[m]==1) m++; else swap(a[m],a[h--]);} for(int i=0;i<n;i++) cout<<a[i]<<(i+1==n?'\n':' ');}
