// Line Container - Deque
/* documents
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

//Code Line Container - Deque
struct Line  // y = a*x + b
{
    ll a,b;
    Line():a(0),b(LLONG_MAX){} 
    Line(ll _a,ll _b):a(_a),b(_b){} 
    
    ll cal(ll x)const {return a * x + b;}
    
      // Compute x coordinate of intersection of two lines
    friend ld xcut(Line a,Line b) { return (ld)(b.b - a.b) / (a.a - b.a);}
    
      // Check if the Line b in the hull is valid
    friend bool check(Line a,Line b,Line c) { return xcut(a,b) < xcut(b,c);}
};

  /* Line Container with constrains:
    'a' values (of inserted lines) are STRICTLY increasing (find Max) or decreasing (find Min)
    'x' values (in queries) are increasing
  */
struct LC_Constrained :deque<Line>
{
    void add(Line a) // O( 1 ) amortized
    {
          // Remove lines while the new line makes the last one invalid
        while(size()>1 && !check(at(size()-2),at(size()-1),a))pop_back();
        pb(a); // Add new line to the back
    }
    
    ll cal(ll x) // O( 1 ) amortized
    {
        if(empty())return LLONG_MAX; // If no lines, return infinity (or whatever)
        
          // Pop useless lines
        while(size()>1 && xcut(at(0),at(1)) < x)pop_front();
        
        return at(0).cal(x); 
    }
};
//End Code Line Container - Deque


pii a[maxn];
vector<pii> b;
ll dp[maxn];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://oj.vnoi.info/problem/group
    
    int n;
    cin>>n;
    
    for(int i = 0;i<n;i++)  cin>>a[i].fi>>a[i].se;
    
    sort(a,a+n,greater<>());
    
    for(int i = 0,mx = 0;i<n;i++)
    {
        if(a[i].se>mx)
        {
            mx=a[i].se;
            b.pb(a[i]);
        }
    }
    
    LC_Constrained CHT; 
    int i = 1;
        
    for(pii k : b)
    {
        dp[i] = dp[i-1] + k.fi * k.se;
          
        if(CHT.size()) dp[i] = min( dp[i], CHT.cal(k.se) ); // Use CHT to get minimum 
          
        CHT.add( Line(k.fi,dp[i-1]) ); // Add new line to CHT for future queries
        i++;
    }
    
    cout<<dp[b.size()];
    
    return 0;
}
