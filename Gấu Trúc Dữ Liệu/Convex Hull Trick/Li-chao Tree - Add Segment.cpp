// Li-chao Tree - Add Segment
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
    ll cal(ll x) const {return a * x + b;}
};

struct Lichao 
{
    vector<Line> t;
    
    Lichao(){} 
      // Initialize tree with given size (for segment tree)
    Lichao(int sz) : t(sz * 4,Line(0,LLONG_MAX)){}
    
      // Insert a new line f into the segment tree
    void add_line(int i,int tl,int tr,Line f)
    {
        int mid = (tl + tr)/2;
          // Swap if new line is better at midpoint
        if( f.cal(mid) < t[i].cal(mid) ) swap(t[i],f);
        
        if(tl == tr) return; // Leaf node reached
        
          // Decide which child to update based on slopes
        if(f.a > t[i].a) add_line(i * 2,tl,mid,f); // higher slope -> left side of the convex hull
        if(f.a < t[i].a) add_line(i * 2 + 1,mid+1,tr,f); // otherwise
    }
    
    void add_segment(int i,int l,int r,int tl,int tr,Line f)
    {
        if(tl > tr || tl > r || tr < l)return ;
        if(tl >= l && tr <= r)
        {
            add_line(i,tl,tr,f);
            return;
        }
        int mid = (tl + tr)/2;
        add_segment(i*2,l,r,tl,mid,f);
        add_segment(i*2+1,l,r,mid+1,tr,f);
    }
    
      // Query minimum value at position pos
    ll cal(int i,int tl,int tr,int pos)
    {
        if(tl > tr || tl > pos || tr < pos)return LLONG_MAX;
        ll ans = t[i].cal(pos); // Value for current node
        if(tl == tr)return ans; // Leaf node
        
        int mid = (tl + tr)/2;
          // Query both children and return minimum value
        ans = min(ans, cal(i*2,tl,mid,pos) );
        ans = min(ans, cal(i * 2 + 1,mid+1,tr,pos) );
        return ans;
    }
};
// End Code Li-chao Tree

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    Lichao tree(1000000 + 10);
    
    
    return 0;
}