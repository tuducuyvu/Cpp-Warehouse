//Diophantine
/* documents
https://cp-algorithms.com/algebra/linear-diophantine-equation.html
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

//Diophantine code
  // Extended Euclidean Algorithm: finds x, y such that a*x + b*y = gcd(a, b)
ll local_gcd(ll a,ll b,ll &x,ll &y) // O( log(min(a,b)) )
{
  if(b==0)
  {
    x = 1;
    y = 0;
    return a;
  }
  ll x1,y1;
  ll ans = local_gcd(b,a%b,x1,y1);
  x = y1; // Update x for current recursion
  y = x1 - y1 * (a/b); // Update y for current recursion
  return ans;
}

  // Solves a*x + b*y = c for integers x, y. Returns true if solution exists.
bool diophantine(ll a,ll b,ll c, ll &x,ll &y,ll &g) // O( log(min(a,b)) )
{
  g = local_gcd(abs(a),abs(b),x,y); // Get gcd and coefficients
  if(c % g)return 0; // No solution if c not divisible by gcd
  x *= c / g;
  y *= c / g;
  if(a<0)x = -x; // Adjust sign of x if needed
  if(b<0)y = -y; // Adjust sign of y if needed
  return 1;
}
//End Diophantine code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}