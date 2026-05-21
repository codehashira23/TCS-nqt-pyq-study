/*
   TCS NQT PYQ 46: Caesar Cipher (With Digits)
   Source: Verified PYQ
   Difficulty: Medium
   Topics: String, Cipher

   QUESTION
   Implement a Caesar Cipher that works on both alphabets and digits. Given a plaintext string and a key K, shift letters (uppercase and lowercase) and digits by K positions with wrap-around. Special characters remain unchanged.

   CONSTRAINTS
   - 1 <= length of string <= 100000.
   - Input is assumed valid unless the problem explicitly asks for validation.
   - Use O(N) or better whenever a direct traversal solution exists.

   INPUT FORMAT
   The string input described in the question.

   OUTPUT FORMAT
   The required string/count/result.

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

bool valid(const string& s){bool upper=false,digit=false; if(s.size()<4||isdigit((unsigned char)s[0])) return false; for(char c:s){if(c==' '||c=='/') return false; upper|=isupper((unsigned char)c); digit|=isdigit((unsigned char)c);} return upper&&digit;}
char shiftChar(char c,int k){if(isupper((unsigned char)c)) return char('A'+(c-'A'+k)%26); if(islower((unsigned char)c)) return char('a'+(c-'a'+k)%26); if(isdigit((unsigned char)c)) return char('0'+(c-'0'+k)%10); return c;}
int main(){string s; int k; getline(cin,s); cin>>k; if(!valid(s)){cout<<"Error!\n"; return 0;} for(char &c:s) c=shiftChar(c,k); cout<<s<<"\n";}
