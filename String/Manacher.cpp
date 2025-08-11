//Manacher
/* documents
 https://wiki.vnoi.info/algo/string/manacher
 https://cp-algorithms.com/string/manacher.html
*/
#include <bits/stdc++.h>

using namespace std;
#define all(v) v.begin(),v.end()
#define pb push_back
#define ll long long
#define ld long double
#define fi first
#define se second
#define mk make_pair
typedef pair<int,int> pii;

const int maxn = 2e6 + 10;

// Manacher code
int pal_len[maxn],pal_r[maxn];

  // Converts the input string by inserting '#' between every character to handle both even and odd length palindromes in 1 function
string change_format(string text) // O( n )
{
  string s = "#";
  for(int ch : text)
  {
    s += ch;
    s += '#';
  }
  return s;
}

  // Finds the length of the longest palindrome centered at each position in s
void manacher(string s) // O( n )
{
  int n = s.size();
  
  int l = 0,r = 0; // current palindrome's left and right boundaries
  for(int i = 1;i<n;i++)
  {
    // If i is within [l, r], use previously calculated palindrome info
    if(i <= r)pal_len[i] = min(r - i, pal_len[r - i + l]);
    else pal_len[i] = 0;
    
    // Try to expand palindrome centered at i
    while(i + pal_len[i] + 1 < n && i - pal_len[i] - 1 >= 0 && s[i + pal_len[i] + 1] == s[i - pal_len[i] - 1] ) pal_len[i]++;
    
    // Update [l, r] 
    if(i + pal_len[i] > r)
    {
      l = i - pal_len[i];
      r = i + pal_len[i];
    }
    
    pal_r[i] = pal_len[i]/2;// Store half the length for easy access to original string palindromes
  }
}
//End Manacher code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://judge.yosupo.jp/problem/enumerate_palindromes
    
    string s;
    cin>>s;
    
    s = change_format(s); // convert string for Manacher's algorithm
    int n = s.size();
    
    manacher(s); 
    
    // Output the max length of palindrome centered in each position ( a character of s or between 2 characters ) 
    for(int i = 1;i<n-1;i++)cout<<pal_len[i]<<' ';
    
    return 0;
}