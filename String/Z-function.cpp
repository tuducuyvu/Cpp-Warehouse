//Z-function
/* documents
 https://wiki.vnoi.info/algo/string/z-algo
 https://cp-algorithms.com/string/z-function.html
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

// Z-function code
int z[maxn]; // z[i] = length of longest prefix starting at i that matched the prefix of whole string

  // Calculates Z-array for string s 
void z_function(string s) // O( n )
{
  int l = 1,r = 0;
  for(int i = 1;i<s.size();i++)
  {
    // If i is within [l, r], use previously computed values to initialize z[i]
    if(i <= r)z[i] = min(r - i + 1,z[i-l]);
    else z[i] = 0;
    
    while(i + z[i]<s.size() && s[i + z[i]] == s[z[i]])z[i]++;
    
    if(i + z[i] - 1 > r)// Update [l, r] if we extended past r
    {
      r = i + z[i] - 1;
      l = i;
    }
  }
}
//End Z-function code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://oj.vnoi.info/problem/substr
    
    string text,pattern;
    cin>>text>>pattern;
    
    int n = pattern.size(), m = text.size();
    
    z_function(pattern + '%' + text); // Run Z-function on combined string
    
    // Output positions where pattern occurs in text
    for(int i = n + 1;i<=n + m;i++)
    {
      if(z[i] == n)cout<<i - n<<'\n';
    }
    
    return 0;
}