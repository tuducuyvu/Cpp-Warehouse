// Line Container - MultiSet
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

//Code Line Container - MultiSet
struct Line // y = ax + b
{
    ll a,b;
    mutable ld p; // position where this line intersects with next line in the container (aka where this line ends)
    Line():a(0),b(0),p(LLONG_MAX){}
    Line(ll _a,ll _b):a(_a),b(_b),p(LLONG_MAX){}
    
    ll cal(ll x) const {return a * x + b;}
    
      // Comparison operator for querying
    bool operator < (const ll & x) const { return p < x;}
    
      // Comparison operator for set ordering (For finding Max, just reverse everything in here)
    bool operator < (const Line &o) const 
    {
        if(a != o.a)return a > o.a;
        return b < o.b;
    }
};

  // UNLIMITED POWER
struct LC_General : multiset<Line, less<void>>
{
      // Calculate intersection (cut) point between two lines
    ld xcut(iterator a,iterator b) const { return (ld)(b->b - a->b) / (a->a - b->a);}
    
      // Checks if line 'b' is valid
    bool check(iterator a,iterator b) // O( 1 )
    {
        if(b == end())
        {
            a->p = LLONG_MAX; // the last line ends at infinity
            return 1;
        }
        
        if(a->a == b->a)return 0; // Parallel lines, and since our comparator ensured that a->b <= b->b , line 'b' is useless
        
        a->p = xcut(a,b); // recalculate intersection
        return a->p < b->p;
    }
    
      // Add a new line to the container & maintain structure
    void add(Line A) // O( log(n) ) amortized
    {
        iterator a = insert(A);
        iterator b = next(a);
          // Remove invalid lines behind the new line
        while(!check(a,b)) b = erase(b); 
        
          // Same, but infront
        bool forced = 1; // we must check the new line's validity AND atleast one of the lines infront
        while(a != begin())
        {
            b = a;
            a = prev(a);
            if(!check(a,b)) check(a,erase(b)); // erase 'b' and recalculate a->p
            else if(!forced) break;
            forced = 0;
        }
    }
    
      // Query the minimum value at x
    ll cal(ll x)  // O( log(n) )
    {
        return lower_bound(x)->cal(x); 
    }
};
//End Code Line Container - MultiSet

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
    
    LC_General CHT; 
    
    for(int i = 1;i<=n;i++)
    {
        if(i == 1)  dp[i] = 0; 
        else  dp[i] = CHT.cal(a[i]) + a[i] * a[i] + pre[i-1];
          // Add new line for future DP queries
        CHT.add(Line( a[i] * -2, a[i] * a[i] - pre[i] + dp[i] ));
    }
    
    cout<<dp[n]; 
    
    return 0;
}
