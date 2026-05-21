/*
   TCS NQT PYQ 66: Alice's Verbal Kho-Kho — Digit Passing Game
   Source: Verified PYQ
   Difficulty: Medium
   Topics: Math, Simulation

   QUESTION
   Alice gives a digit to the first friend. Each friend passes the digit to the next friend. A confused friend passes digit+1 (with wrap-around 9->0). Given starting digit S, number of friends N, and final digit F, find how many confusions occurred.

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

int main(){int s,n,f; cin>>s>>n>>f; int expected=s%10; int diff=(f-expected+10)%10; cout<<diff<<"\n";}
