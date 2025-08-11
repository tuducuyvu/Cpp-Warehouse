// Segment Tree Classic
/* documents
 https://wiki.vnoi.info/vi/algo/data-structures/segment-tree-basic
 https://cp-algorithms.com/data_structures/segment_tree.html
 https://wiki.vnoi.info/algo/data-structures/segment-tree-extend
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

const int maxn = 2e5 + 10;

// Segment Tree Classic code
int a[maxn];
int t[maxn*4],pos_in_tree[maxn];

  // Build the segment tree from the 'a' array
void build(int i,int l,int r) // O( n * 2 )
{
  if(l == r)
  {
    t[i] = a[l]; // Set leaf node value
    pos_in_tree[l] = i; // Map array index to leaf position
  }
  else
  {
    int mid = (l + r)/2,ii = i * 2;
    build(ii,l,mid); // Build left child
    build(ii+1,mid+1,r); // Build right child
    t[i] = min(t[ii],t[ii+1]);
  }
}

  // Update value at position i in the array
  // I made it non-recursive and dont use unnecessary function calls
void up(int i,int val) // O( log(n) )
{
  i = pos_in_tree[i]; // Get leaf position for array index
  t[i] = val; // Update value at the leaf
  // Update ancestors
  for(i>>=1;i;i>>=1)
  {
    t[i] = min(t[i*2],t[i*2+1]);
  }
}

  // Query for minimum in range [l, r]
int cal(int i,int l,int r,int tl,int tr) // O( log(n) )
{
  if(l > r || tl > r || tr < l)return INT_MAX; // not in range [l,r]
  if(tl >= l && tr <= r)return t[i]; // Completely in range [l,r]
  int mid = (tl + tr)/2,ii = i * 2;
  // Query left and right children
  return min(cal(ii,l,r,tl,mid) , cal(ii+1,l,r,mid+1,tr));
}
//End Segment Tree Classic code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/1649
    
    int n,m;
    cin>>n>>m;
    for(int i = 1;i<=n;i++)cin>>a[i];

    build(1,1,n); // Build segment tree

    while(m--)
    {
      int i;
      cin>>i;
      if(i == 1)
      {
        int k,x;
        cin>>k>>x;
        up(k,x); // Update operation
      }
      else
      {
        int l,r;
        cin>>l>>r;
        cout<<cal(1,l,r,1,n)<<'\n'; // Range query operation
      }
    }

    return 0;
}