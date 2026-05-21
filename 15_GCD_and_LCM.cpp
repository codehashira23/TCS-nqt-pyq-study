/*
   TCS NQT PYQ 15: GCD and LCM
   Source: Verified PYQ
   Difficulty: Easy
   Topics: Math

   QUESTION
   Given two integers, find their Greatest Common Divisor (GCD) and Least Common Multiple (LCM).

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

int main(){long long a,b; cin>>a>>b; long long g=__gcd(a,b); cout<<"GCD = "<<g<<"\nLCM = "<<(a/g)*b<<"\n";}
