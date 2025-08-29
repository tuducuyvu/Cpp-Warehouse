// Convex Hull Trick - Constrained Container
/* documents
  tài liệu của lanciu
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
typedef pair<ll,ll> pii;

const int maxn = 3e5 + 10;
pii a[maxn];
vector<pii> b;
ll dp[maxn];

//Code Convex Hull Trick - Constrained Container
struct Line 
{
    ll a,b;
    Line():a(0),b(0){} // Default constructor
    Line(ll A,ll B):a(A),b(B){} // Parameterized constructor
    
      // Calculate y = ax + b for given x
    ll cal(ll x)const {return a * x + b;}
      // Compute x coordinate of intersection between two lines
    friend ld xcut(Line a,Line b) { return (ld)(b.b - a.b) / abs(a.a - b.a);}
      // Check if the Line b in the hull is valid
    friend bool check(Line a,Line b,Line c) { return xcut(a,b) < xcut(b,c);}
};

  // Convex Hull Trick deque with constrains ( a values are STRICTLY decreasing, x queries are increasing )
struct CHT_Constrained :deque<Line>
{
      // Add a new line to the convex hull, removing invalid lines
    void add(Line a)
    {
          // Remove lines while the new line makes the last one invalid
        while(size()>1 && !check(at(size()-2),at(size()-1),a))pop_back();
        pb(a); // Add new line
    }
    
      // Query minimum value for given x
    ll cal(ll x)
    {
        if(empty())return LLONG_MAX; // If no lines, return infinity
          // Pop lines from front while next line gives smaller value
        while(size()>1 && xcut(at(0),at(1)) < x)pop_front();
        return at(0).cal(x); // Return value from optimal line
    }
};
//End Code Convex Hull Trick - Constrained Container

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://oj.vnoi.info/problem/group
    
    int n,mx = 0;
    cin>>n;
    
    for(int i = 0;i<n;i++)
    {
      cin>>a[i].fi>>a[i].se;
    }
    
    sort(a,a+n,greater<>());
    
    for(int i = 0;i<n;i++)
    {
      if(a[i].se>mx)
      {
        mx=a[i].se;
        b.pb(a[i]);
      }
    }
    
    n = b.size();
    int i = 1;
    
    CHT_Constrained container; 
    
    
    for(pii k : b)
    {
      
      dp[i] = dp[i-1] + k.fi * k.se;
        
      if(container.size()) dp[i] = min( dp[i], container.cal(k.se) ); // Use CHT to get minimum possible value if available
        
      container.add( Line(k.fi,dp[i-1]) ); // Add new line to CHT for future queries
      i++;
    }
    
    cout<<dp[n];
    
    return 0;
}