/*
   TCS NQT PYQ 23: Fibonacci Series — Nth Term
   Source: Verified PYQ
   Exam/Shift: 14 May 2024 Shift 1
   Difficulty: Easy
   Topics: Dynamic Programming, Math

   QUESTION
   Find the Nth Fibonacci number where F(1)=1, F(2)=1, and F(N)=F(N-1)+F(N-2).

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

int main(){int n; cin>>n; long long a=1,b=1; if(n<=2){cout<<1<<"\n"; return 0;} for(int i=3;i<=n;i++){long long c=a+b; a=b; b=c;} cout<<b<<"\n";}
