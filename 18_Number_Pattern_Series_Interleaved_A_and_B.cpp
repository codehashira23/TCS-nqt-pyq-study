/*
   TCS NQT PYQ 18: Number Pattern Series (Interleaved A and B)
   Source: Verified PYQ
   Exam/Shift: 26 April 2024 Shift 2
   Difficulty: Easy
   Topics: Math, Series

   QUESTION
   Two number series are interleaved: Series A = 1,2,3,... and Series B = 1,4,9,16,... (squares). The merged sequence is: 1,1,2,4,3,9,4,16,5,25,... Given N, find the Nth term of the merged series.

   CONSTRAINTS
   - Values fit in signed 64-bit integers unless stated otherwise.
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

int main(){long long n; cin>>n; long long k=(n+1)/2; cout<<(n%2?k:k*k)<<"\n";}
