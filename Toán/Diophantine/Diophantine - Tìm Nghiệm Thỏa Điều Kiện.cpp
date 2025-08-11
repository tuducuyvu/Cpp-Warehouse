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
  g = local_gcd(abs(a),abs(b),x,y); // Get gcd and coefficients for equation
  if(c % g)return 0; // No solution if c not divisible by gcd(a, b)
  x *= c / g;
  y *= c / g;
  if(a<0)x = -x; // Adjust sign of x if a is negative
  if(b<0)y = -y; // Adjust sign of y if b is negative
  return 1;
}
//End Diophantine code

//Constrained Diophantine code

  // Shifts the current solution to another solution t times
void shift(ll &x,ll &y,ll a,ll b,ll t) // O( 1 )
{
  x += b * t;
  y -= a * t;
}

  /* (!) function "diophantine_count" can be adapted to 
  -return solution that satisfy constrains
  -only use Min or Max constrain
  */
  
  // Counts the number of solutions for ax + by = c with x in [minx, maxx], y in [miny, maxy]
ll diophantine_count(ll a,ll b,ll c,ll minx,ll maxx,ll miny,ll maxy) // O( log(min(a,b)) )
{
  ll x,y,g;
  if(!diophantine(a,b,c,x,y,g))return 0; // No solution exists
  a/=g;
  b/=g;
  int sign_a = a / abs(a); // a != 0    (!)
  int sign_b = b / abs(b); // b != 0    (!)
  
  shift(x,y,a,b,(minx - x) / b); // Move x to be at least minx
  if(x < minx)shift(x,y,a,b,sign_b);
  if(x > maxx)return 0;
  ll l0 = x;
  
  shift(x,y,a,b,(maxx - x)/b); // Move x to be at most maxx
  if(x > maxx)shift(x,y,a,b,-sign_b);
  ll r0 = x;
  
  shift(x,y,a,b,-(miny - y) / a); // Move y to be at least miny
  if(y < miny)shift(x,y,a,b,-sign_a);
  if(y > maxy)return 0;
  ll l1 = x;
  
  shift(x,y,a,b,-(maxy - y)/a); // Move y to be at most maxy
  if(y > maxy)shift(x,y,a,b,sign_a);
  ll r1 = x;
  
  if(l1>r1)swap(l1,r1);
  ll l = max(l0,l1);
  ll r = min(r0,r1);
  if(l > r)return 0;
  return (r - l) / abs(b) + 1; // Number of valid solutions
}
//End Constrained Diophantine code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}