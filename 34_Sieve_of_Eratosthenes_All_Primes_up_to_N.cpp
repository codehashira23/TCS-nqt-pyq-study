/*
   TCS NQT PYQ 34: Sieve of Eratosthenes — All Primes up to N
   Source: Practice
   Difficulty: Medium
   Topics: Math, Prime, Sieve

   QUESTION
   Print all prime numbers from 2 to N using the Sieve of Eratosthenes.

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

int main(){int n; cin>>n; vector<bool> prime(n+1,true); if(n>=0) prime[0]=false; if(n>=1) prime[1]=false; for(long long p=2;p*p<=n;p++) if(prime[p]) for(long long q=p*p;q<=n;q+=p) prime[q]=false; for(int i=2;i<=n;i++) if(prime[i]) cout<<i<<" "; cout<<"\n";}
