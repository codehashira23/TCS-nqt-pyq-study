/*
   TCS NQT PYQ 63: Count Sundays in a Month
   Source: Verified PYQ
   Difficulty: Easy
   Topics: Simulation, Calendar

   QUESTION
   Jack loves Sundays. Given the day on which a month starts (e.g., "mon", "tue") and the total number of days in that month, find how many Sundays occur in that month.

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

int main(){string start; int days; cin>>start>>days; vector<string>d={"mon","tue","wed","thu","fri","sat","sun"}; int idx=find(d.begin(),d.end(),start)-d.begin(),cnt=0; for(int day=1;day<=days;day++) if((idx+day-1)%7==6) cnt++; cout<<cnt<<"\n";}
