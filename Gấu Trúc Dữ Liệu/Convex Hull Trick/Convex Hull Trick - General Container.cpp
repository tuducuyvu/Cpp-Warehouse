// Convex Hull Trick - General Container 
/* documents
  https://usaco.guide/adv/line-container?lang=cpp
  https://usaco.guide/plat/convex-hull-trick
  https://cp-algorithms.com/geometry/convex_hull_trick.html
  https://wiki.vnoi.info/algo/dp/cht
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

// Code Convex Hull Trick - General Container
struct Line // y = ax + b
{
    ll a,b;
    mutable ld p; // the position where this line intersects with the next line in the container
    Line():a(0),b(0),p(LLONG_MIN){}
    Line(ll A,ll B):a(A),b(B),p(LLONG_MIN){}
    
    
    ll cal(ll x) const {return a * x + b;}
    
      // Comparison operator for querying
    bool operator < (const ll & x) const { return p < x;}
    
      // Comparison operator for set ordering
    bool operator < (const Line &o) const 
    {
        if(a != o.a)return a > o.a;
        return b < o.b;
    }
};

  // Convex Hull Trick General Container using multiset
struct CHT_General : multiset<Line,less<void>>
{
      // Calculate intersection (cut) point between two lines
    ld xcut(iterator a,iterator b) const { return (ld)(b->b - a->b) / abs(a->a - b->a);}
    
      // Checks if line a should remain before line b
    bool check(iterator a,iterator b)
    {
        if(b == end())
        {
            a->p = LLONG_MAX; // Set p as infinity for the last line
            return 1;
        }
        
        if(a->a == b->a)return 0; // Parallel lines
        
        a->p = xcut(a,b); // recalculate x intersection
        return a->p < b->p;
    }
    
      // Add a new line to the container, maintaining optimal structure
    void add(Line A)
    {
        iterator a = insert(A);
        iterator b = next(a);
        while(!check(a,b)) b = erase(b); // Remove useless lines after a
        
        if(a != begin())
        {
            b = prev(a);
            if(!check(b,a)) check(b,erase(a));
        }
        else return;
        
          // Check previous lines to maintain container integrity
        while(b != begin())
        {
            a = prev(b);
            if(a->p >= b->p)
            {
                check(a,erase(b)); // erase b and recalculate a->p
                b = a;
            }
            else break;
        }
    }
    
      // Query the minimum value at x
    ll cal(ll x) { return lower_bound(x)->cal(x); }
};
// End Code Convex Hull Trick - General Container

ll a[maxn],pre[maxn],dp[maxn];

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
    
    CHT_General container; 
    
    for(int i = 1;i<=n;i++)
    {
        if(i == 1)
        {
            dp[i] = 0; 
        }
        else
        {
            dp[i] = container.cal(a[i]) + a[i] * a[i] + pre[i-1];
        }
          // Add new line for future DP queries
        container.add(Line( a[i] * -2, a[i] * a[i] +dp[i] - pre[i] ));
    }
    
    cout<<dp[n]; 
    
    return 0;
}
