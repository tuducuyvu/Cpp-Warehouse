// Li-chao Tree
/* documents
  https://wiki.vnoi.info/vi/algo/data-structures/lichao-tree
  https://cp-algorithms.com/geometry/convex_hull_trick.html
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
ll a[maxn],pre[maxn],dp[maxn];

// Code Li-chao Tree
struct Line 
{
    ll a,b;
    Line():a(0),b(0){}
    Line(ll A,ll B) : a(A),b(B){}
    
      // Calculate value of line at point x
      // Returns y = ax + b
    ll cal(ll x) const {return a * x + b;}
};

struct Lichao 
{
  vector<Line> t;
  
  Lichao(){} 
    // Initialize tree with given size (for segment tree)
  Lichao(int sz) : t(sz,Line(0,LLONG_MAX)){}
  
    // Insert a new line f into the segment tree
    // l, r: current segment range in coordinate space
    // f: line to insert
  void add_line(int l,int r,Line f) // O( log(sz) )
  {
      if(l > r)return;
      int mid = (l + r)/2;
        // Swap if new line is better at midpoint
      if( f.cal(mid) < t[mid].cal(mid) ) swap(t[mid],f);
      
      if(l == r) return; // Leaf node reached
      
      if(f.a > t[mid].a) add_line(l,mid-1,f); // higher slope -> left side of the convex hull
      if(f.a < t[mid].a) add_line(mid+1,r,f); // otherwise
  }
  
    // l, r: current segment range
    // pos: query x-coordinate
  ll cal(int l,int r,int pos) // O( log(sz) )
  {
      if(l > r || l > pos || r < pos)return LLONG_MAX;
      
      int mid = (l + r)/2;
      ll ans = t[mid].cal(pos);
      
      if(l == r)return ans; // Leaf node
        // Query both children and return minimum value for pos
      ans = min(ans, cal(l,mid-1,pos));
      ans = min(ans, cal(mid+1,r,pos) );
      return ans;
  }
};
// End Code Li-chao Tree

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://oj.uz/problem/view/CEOI17_building?locale=en
    
    int n;
    cin>>n;
    for(int i = 1;i<=n;i++)cin>>a[i];
    for(int i = 1;i<=n;i++)
    {
        cin>>pre[i];
        pre[i] += pre[i-1]; 
    }
    
    Lichao tree(1000000 + 10); // Initialize Li-chao tree to cover possible x values
    
    for(int i = 1;i<=n;i++)
    {
        if(i == 1)
        {
            dp[i] = 0; 
        }
        else
        {
            dp[i] = tree.cal(0,1000000,a[i]) + a[i] * a[i] + pre[i-1];
        }
        // Add new line for future DP queries (state transition)
        tree.add_line(0,1000000,Line( a[i] * -2, a[i] * a[i] +dp[i] - pre[i] ));
    }
    
    cout<<dp[n]; 
    
    return 0;
}