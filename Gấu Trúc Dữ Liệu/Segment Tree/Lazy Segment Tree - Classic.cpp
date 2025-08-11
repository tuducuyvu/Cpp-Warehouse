// Lazy Segment Tree - Classic
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

const int maxn = 1e5 + 10;

// Lazy Segment Tree - Classic code
int a[maxn];
int t[maxn*4],lazy[maxn*4];

  // Build the segment tree from the 'a' array
void build(int i,int l,int r) // O( n * 2 )
{
  if(l == r)
  {
    t[i] = a[l]; // Set leaf node value
  }
  else
  {
    int mid = (l + r)/2,ii = i * 2;
    build(ii,l,mid); // Build left child
    build(ii+1,mid+1,r); // Build right child
    t[i] = min(t[ii],t[ii+1]); // update this node after children
  }
}

void push(int i,int l,int r) // O( 1 )
{
  if(lazy[i] == 0)return; // No pending update
  t[i] += lazy[i]; // Apply pending update to current node
  if(l != r)
  {
    lazy[i*2] += lazy[i]; // Propagate to left child
    lazy[i*2+1] += lazy[i]; // Propagate to right child
  }
  lazy[i] = 0; // Clear lazy value
}

  // update : add 'val' to [l,r]
void up(int i,int l,int r,int tl,int tr,int val) // O( log(n) ) 
{
  push(i,tl,tr); // Ensure any pending updates are applied
  if(l > r || tl > r || tr < l)return; // not in range [l,r]
  if(tl >= l && tr <= r)// Completely in range [l,r]
  {
    lazy[i] += val; // Mark lazy update
    push(i,tl,tr); // Apply update
    return;
  }
  int mid = (tl + tr)/2,ii = i * 2;
  // update left and right children
  up(ii,l,r,tl,mid,val);
  up(ii+1,l,r,mid+1,tr,val);
  t[i] = min(t[ii],t[ii+1]); // Update this node after children
}

  // Query for minimum in range [l, r]
int cal(int i,int l,int r,int tl,int tr) // O( log(n) )
{
  push(i,tl,tr);  // Ensure any pending updates are applied
  if(l > r || tl > r || tr < l)return INT_MAX; // not in range [l,r]
  if(tl >= l && tr <= r)return t[i]; // Completely in range [l,r]
  int mid = (tl + tr)/2,ii = i * 2;
  // Query left and right children
  return min(cal(ii,l,r,tl,mid) , cal(ii+1,l,r,mid+1,tr));
}
//End Lazy Segment Tree - Classic code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://marisaoj.com/problem/204
    
    int n,m;
    cin>>n>>m;
    for(int i = 1;i<=n;i++)cin>>a[i];

    build(1,1,n);

    while(m--)
    {
      int i;
      cin>>i;
      if(i == 1)
      {
        int l,r,x;
        cin>>l>>r>>x;
        up(1,l,r,1,n,x); // Update operation
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