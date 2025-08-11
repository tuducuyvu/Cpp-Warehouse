//Prefix Function + KMP 
/* documents
 https://wiki.vnoi.info/algo/string/kmp
 https://cp-algorithms.com/string/prefix-function.html
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

const int maxn = 2e6 +10;

// Prefix Function code
int pf[maxn];

  // Computes the prefix function for string s
void prefix_function(string s) // O( n )
{
  // i: current position in string, j: length of current matching prefix
  for(int i = 1,j = 0;i<s.size();i++)
  {
      // Update j as long as mismatch occurs and j > 0
    while(j && s[i] != s[j])j = pf[j-1];
      // If match, extend prefix length
    if(s[i] == s[j])j++;
      // Store length of longest prefix which is also suffix for position i
    pf[i] = j;
  }
}
//End Prefix Function code

// KMP code
  // Finds all occurrences of pattern in text and outputs their positions (1-based)
void KMP(string text,string pattern) // O( n + m )
{
  int n = pattern.size(),m = text.size();
  
  prefix_function(pattern); // Build prefix function for pattern
  
  for(int i = 0,j = 0;i<m;i++)
  {
      // Update j as long as mismatch occurs and j > 0
    while(j && text[i] != pattern[j])j = pf[j-1];
      // If match, extend prefix length
    if(text[i] == pattern[j])j++;
    
    if(j == n) // found pattern in text
    {
      cout<<i - n + 2<<'\n'; // output position of occurrences
    }
  }
}
//End KMP code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://oj.vnoi.info/problem/substr
    
    string text,pattern;
    cin>>text>>pattern;
    
    KMP(text,pattern); // Find and output all occurrences of pattern in text
    
    return 0;
}