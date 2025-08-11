//Prime check
/* documents
https://wiki.vnoi.info/vi/algo/algebra/primality_check
https://cp-algorithms.com/algebra/primality_tests.html#fermat-primality-test
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

// bin_pow code
  // Computes (a * b) % mod using binary multiplication to avoid overflow
ll bin_mul(ll a,ll b,const ll &mod) // O( log(b) )
{
  a %= mod;
  ll ans = 0;
  for(;b;b>>=1)
  {
    if(b&1)ans = (ans + a) % mod; // Add a to result if lowest bit is set
    a = (a + a) % mod; // Double a at each step
  }
  return ans;
}

  // Computes (a^b) % mod using binary exponentiation (mod is int)
ll bin_pow(ll a,ll b,const int &mod) // O( log(b) )
{
  a %= mod;
  ll ans = 1;
  for(;b;b>>=1)
  {
    if(b&1)ans = ans * a % mod; // Multiply ans by a if lowest bit is set
    a = a * a % mod; // Square a at each step
  }
  return ans;
}

  // Computes (a^b) % mod with large mod using safe multiplication
ll bin_pow_large_mod(ll a,ll b,const ll &mod) // O( log(b) * log(mod) )
{
  a %= mod;
  ll ans = 1;
  for(;b;b>>=1)
  {
    if(b&1)ans = bin_mul(ans , a , mod); // Use bin_mul for safe multiplication
    a = bin_mul(a , a , mod);
  }
  return ans;
}
//End bin_pow code

// Prime check code
const vector<int> check_set = {2,3,5,7,11,13,17,19,23,29,31,37};

bool check_composite_int(int a,int mod,int t,int m) // O( log(n) )
{
  // checks if 'a' is a composite witness for mod
  // if you are confused, pls check documents
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
  // Miller-Rabin test for int n
  for(int k : check_set)if(n == k)return 1;
  if(n < 41)return 0;
  
  int m = n - 1;
  int t = __builtin_ctz(m); // Count trailing zeros in (n-1)
  m>>=t;
  for(int k : check_set)if(check_composite_int(k,n,t,m))return 0;
  return 1;
}

bool check_composite_longlong(ll a,ll mod,int t,ll m) // O( log(n) )
{
  // checks if 'a' is a composite witness for mod (long long)
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
  // Miller-Rabin test for long long n
  for(int k : check_set)if(n == k)return 1;
  if(n < 41)return 0;
  
  ll m = n - 1;
  int t = __builtin_ctzll(m); // Count trailing zeros in (n-1)
  m>>=t;
  for(int k : check_set)if(check_composite_longlong(k,n,t,m))return 0;
  return 1;
}
//End prime check code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}