/*
   TCS NQT PYQ 45: MPCS Fitness Test — Average Oxygen Level of Trainees
   Source: Verified PYQ
   Difficulty: Medium
   Topics: Arrays

   QUESTION
   A batch of 3 trainees runs for 3 rounds. Record their oxygen level after every round (must be between 1 and 100). After all rounds, calculate each trainee's average oxygen level and select the trainee(s) with the highest average as "most fit". If all averages are below 70, declare "All trainees are unfit."

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

int main(){int a[3]={0,0,0}; for(int r=0;r<3;r++) for(int t=0;t<3;t++){int x; cin>>x; if(x<1||x>100){cout<<"Invalid input\n"; return 0;} a[t]+=x;} int best=max({a[0],a[1],a[2]}); if(best/3<70) cout<<"All trainees are unfit.\n"; else for(int i=0;i<3;i++) if(a[i]==best) cout<<"Trainee Number: "<<i+1<<"\n";}
