/*
   TCS NQT PYQ 07: Income, Expenditure and Savings Tracker
   Source: Verified PYQ
   Difficulty: Medium
   Topics: Simulation, Maps

   QUESTION
   Continuously take user input for income amount, type of material (category of expenditure), and expenditure on that material until the user enters "done". Then display total income, total savings (income minus total expenditure), and the list of where money was spent with respective amounts.

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

int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
    double totalIncome=0,totalExpense=0; map<string,double> spent; string category;
    while(cin>>category && category!="done"){double income,expense; cin>>income>>expense;
        totalIncome+=income; totalExpense+=expense; spent[category]+=expense;
    }
    cout<<"Total Income: "<<fixed<<setprecision(2)<<totalIncome<<"\n";
    cout<<"Total Savings: "<<totalIncome-totalExpense<<"\n";
    for(auto &p:spent) cout<<p.first<<" "<<p.second<<"\n";
}
