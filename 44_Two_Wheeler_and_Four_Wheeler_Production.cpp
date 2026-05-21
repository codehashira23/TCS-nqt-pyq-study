/*
   TCS NQT PYQ 44: Two-Wheeler and Four-Wheeler Production
   Source: Verified PYQ
   Difficulty: Easy
   Topics: Math

   QUESTION
   An automobile company manufactures two-wheelers (TW) and four-wheelers (FW). Given the total number of vehicles V and the total number of wheels W, determine how many TW and FW are manufactured. If the inputs do not yield a valid solution, print "INVALID INPUT".

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

int main(){long long v,w; cin>>v>>w; long long fw=(w-2*v)/2, tw=v-fw; if(w%2||fw<0||tw<0||tw+fw!=v) cout<<"INVALID INPUT\n"; else cout<<"TW = "<<tw<<"\nFW = "<<fw<<"\n";}
