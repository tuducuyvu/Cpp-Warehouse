// Large Phi Euler
/* documents
https://wiki.vnoi.info/vi/translate/he/Number-Theory-4
https://cp-algorithms.com/algebra/phi-function.html
https://codeforces.com/blog/entry/106851
https://wiki.vnoi.info/vi/algo/math/integer-factorization
https://cp-algorithms.com/algebra/factorization.html
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
set<ll> factor_set;

// bin_pow code
ll bin_mul(ll a,ll b,const ll &mod) // O( log(b) )
{
  a %= mod;
  ll ans = 0;
  for(;b;b>>=1)
  {
    if(b&1)ans = (ans + a) % mod;
    a = (a + a) % mod;
  }
  return ans;
}

ll bin_pow(ll a,ll b,const int &mod) // O( log(b) )
{
  a %= mod;
  ll ans = 1;
  for(;b;b>>=1)
  {
    if(b&1)ans = ans * a % mod;
    a = a * a % mod;
  }
  return ans;
}

ll bin_pow_large_mod(ll a,ll b,const ll &mod) // O( log(b) * log(mod) )
{
  a %= mod;
  ll ans = 1;
  for(;b;b>>=1)
  {
    if(b&1)ans = bin_mul(ans , a , mod);
    a = bin_mul(a , a , mod);
  }
  return ans;
}
//End bin_pow code

// Prime check code
const vector<int> check_set = {2,3,5,7,11,13,17,19,23,29,31,37};

bool check_composite_int(int a,int mod,int t,int m) // O( log(n) )
{
  ll n = bin_pow(a,m,mod);
  if(n == 1 || n == mod-1)return 0;
  while(t--)
  {
    n = n * n % mod;
    if(n == mod-1)return 0;
  }
  return 1;
}

bool prime_check_int(int n) // O( log(n) ^ 2 )
{
  for(int k : check_set)if(n == k)return 1;
  if(n < 41)return 0;
  
  int m = n - 1;
  int t = __builtin_ctz(m);
  m>>=t;
  for(int k : check_set)if(check_composite_int(k,n,t,m))return 0;
  return 1;
}

bool check_composite_longlong(ll a,ll mod,int t,ll m) // O( log(n) )
{
  ll n = bin_pow_large_mod(a,m,mod);
  if(n == 1 || n == mod-1)return 0;
  while(t--)
  {
    n = bin_mul(n,n,mod);
    if(n == mod-1)return 0;
  }
  return 1;
}

bool prime_check_longlong(ll n) // O( log(n) ^ 2 )
{
  for(int k : check_set)if(n == k)return 1;
  if(n < 41)return 0;
  
  ll m = n - 1;
  int t = __builtin_ctzll(m);
  m>>=t;
  for(int k : check_set)if(check_composite_longlong(k,n,t,m))return 0;
  return 1;
}
//End prime check code

//Random Number Generator code
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random_range(ll l,ll r) // O(1)
{
  return uniform_int_distribution<ll>(l,r)(rng);
}
//End Random Number Generator code

//Pollard Rho code
ll f(ll a,ll b,ll mod) // O( log(a) )
{
  return (bin_mul(a,a,mod) + b)% mod;
}

ll rho(ll n) // O( n ^ 0.25 )
{
  while(1)
  {
    ll c = random_range(0,n-1);
    ll x = random_range(0,n-1);
    ll y = x;
    ll g = 1;
    while(g == 1)
    {
      x = f(x,c,n);
      y = f(y,c,n);
      y = f(y,c,n);
      g = __gcd(abs(x-y),n);
    }
    if(g != n)return g;
  }
}
//End Pollard Rho code

// Small Prime Factor code
void trial_division(ll n) // O( sqrt(n) )
{
  if(n < 2)return;
  for(int k : {2,3,5})
  {
    if(n % k == 0)
    {
      while(n % k == 0)
      {
        n/=k;
      }
      factor_set.insert(k);
    }
  }
  int i = 0;
  const int next[] = {4,2,4,2,4,6,2,6};
  for(ll k = 7;k*k <= n;k+=next[i++],i%=8)
  {
    if(n % k == 0)
    {
      while(n % k == 0)
      {
        n/=k;
      }
      factor_set.insert(k);
    }
  }
  if(n>1)factor_set.insert(n);
}
//End Small Prime Factor code

// Prime Factor Code
void factorise(ll n) // O( n * 0.25 * log(n) )
{
  if(n < 10000)
  {
    trial_division(n);
    return;
  }
  if(prime_check_longlong(n))
  {
    factor_set.insert(n);
    return;
  }
  ll k = rho(n);
  factorise(n/k);
  factorise(k);
}
//End prime factor code

// Large Phi Euler
ll phi_longlong(ll n) // O( n * 0.25 * log(n) )
{
  ll ans = n;
  factor_set.clear();
  factorise(n);
  for(ll k : factor_set)ans -= ans / k;
  return ans;
}
//End Large Phi Euler

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}