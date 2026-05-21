/*
   TCS NQT PYQ 28: Maximum Subarray Sum (Kadane's Algorithm)
   Source: Practice
   Difficulty: Medium
   Topics: Array, Dynamic Programming

   QUESTION
   Given an array of integers (possibly containing negative values), find the sum of the contiguous subarray with the maximum sum.

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

int main(){int n; cin>>n; long long best=LLONG_MIN,cur=0,x; while(n--){cin>>x; cur=max(x,cur+x); best=max(best,cur);} cout<<best<<"\n";}
