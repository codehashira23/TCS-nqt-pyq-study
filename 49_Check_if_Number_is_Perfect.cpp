/*
   TCS NQT PYQ 49: Check if Number is Perfect
   Source: Verified PYQ
   Difficulty: Easy
   Topics: Math

   QUESTION
   A perfect number equals the sum of its proper divisors (excluding itself). Check if a given number N is perfect.

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

int main(){long long n; cin>>n; if(n<=1){cout<<"false\n"; return 0;} long long sum=1; for(long long d=2;d*d<=n;d++) if(n%d==0){sum+=d; if(d*d!=n) sum+=n/d;} cout<<(sum==n?"true":"false")<<"\n";}
