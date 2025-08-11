//Lazy Segment tree 2*n
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

// Lazy Segment Tree 2N - range update, query min
int n;
ll t[maxn*2],lazy[maxn];

void build() // O( n )
{
  for(int i = n-1; i ; i--) t[i] = min(t[i*2], t[i*2+1]);
}

  // Rebuilds the tree upwards from a given position.
void build_from(int i) // O( log(n) )
{
  for(i >>= 1; i ; i >>= 1) t[i] = min(t[i*2], t[i*2+1]) + lazy[i];
}

  // Applies value 'val' to node i, for both direct update and lazy propagation.
void apply(int i, ll val) // O( 1 )
{
  t[i] += val;    // Immediately update the node value.
  if(i < n) lazy[i] += val;// If i < n then it's not a leaf node so we propagate.
}
  
  // Pushes all pending lazy updates from ancestors of pos down to pos.
  // Ensures all updates affecting pos are applied before query.
void push(int pos) // O( log(n) )
{
  // Go from root towards pos, applying lazy values to children.
  for(int j = log2(pos); j ; j--)
  {
    int i = (pos >> j); // i is an ancestor of pos at level j
    // Push lazy value
    apply(i*2, lazy[i]);     
    apply(i*2+1, lazy[i]);   
    lazy[i] = 0;             
  }
}

  // Range update: add val to all elements in [l, r-1].
void up(int l, int r, ll val) // O( log(n) )
{
  l += n; r += n;            // Move to leaf nodes
  int l0 = l, r0 = r;        // Keep original positions for rebuilding ancestor nodes
  // Traverse the segment tree, updating relevant segments.
  for(; l < r; l >>= 1, r >>= 1)
  {
    if(l & 1) apply(l++, val);   // If l is right child, update then move to next
    if(r & 1) apply(--r, val);   // If r is right child, update the previous left child
  }
  build_from(l0);            // rebuild min values from updated left index up
  build_from(r0-1);          // rebuild min values from updated right index up
}

  // Range query: returns minimum in [l, r-1].
ll cal(int l, int r) // O( log(n) )
{
  ll ans = LLONG_MAX;
  l += n; r += n;            // Move to leaf nodes
  push(l);                   // Apply pending updates for left bound
  push(r-1);                 // Apply pending updates for right bound
    // Traverse the segment tree, finding the minimum value in [l, r-1]
  for(; l < r; l >>= 1, r >>= 1)
  {
    if(l & 1) ans = min(ans, t[l++]); // If l is right child, use it then move to next
    if(r & 1) ans = min(ans, t[--r]); // If r is right child, use the previous left child
  }
  return ans; 
}
//End Lazy Segment Tree 2N - range update, query min

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://marisaoj.com/problem/204
    
    int m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)  cin >> t[i+n];
    build();  // Build segment tree from leaves
    
    while(m--)
    {
      int i;
      cin >> i;
      if(i == 1)
      {
        int l, r, x;
        cin >> l >> r >> x;
        up(l, r+1, x);      // Range update: add x to [l, r] 
      }
      else
      {
        int l, r;
        cin >> l >> r;
        cout << cal(l, r+1) << '\n'; // Range query: get min in [l, r] 
      }
    }
    
    return 0;
}