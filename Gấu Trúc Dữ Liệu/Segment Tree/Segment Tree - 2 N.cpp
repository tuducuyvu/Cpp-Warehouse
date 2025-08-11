//Segment tree 2*n
/* documents
https://codeforces.com/blog/entry/18051
https://wiki.vnoi.info/vi/translate/codeforces/Efficient-and-easy-segment-trees
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

const int maxn = 1e5 + 10;

//Segment tree 2*n code
int n;
ll t[maxn * 2 + 10];//segment tree

void build() // O( n )
{
  // Build internal nodes (bottom-up)
  for(int i = n-1; i; i--) 
    t[i] = t[i*2] + t[i*2+1];
}

// Update value at position i to val
void up(int i, int val) // O( log(n) )
{
  i += n; // Move to leaf position
  t[i] = val;
  // Update all ancestors of i
  for(; i > 1; i >>= 1)
    t[i>>1] = t[i] + t[i^1];
}

  // Calculate sum on interval [l, r-1]   (!) its r-1, not r
ll cal(int l, int r) // O( log(n) )
{
  ll ans = 0;
  l += n; // Move to leaf
  r += n; // Move to leaf
    // Traverse up, collecting segments covering [l, r-1]
  for(; l < r; l >>= 1, r >>= 1)
  {
    if(l & 1) ans += t[l++]; // If l is right child, use it then move to next
    if(r & 1) ans += t[--r]; // If r is right child, use the previous left child
  }
  return ans;
}
//End Segment tree 2*n code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}