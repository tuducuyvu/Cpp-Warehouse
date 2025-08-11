//Lucas nCk
/* documents
https://wiki.vnoi.info/vi/algo/algebra/nCk
https://cp-algorithms.com/combinatorics/binomial-coefficients.html
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

const int maxn = 1e6 + 10;
const ll mod = 1e4 + 7;//small prime & constant

//nCk code
ll f[maxn],invf[maxn]; // factorial[] , inverse modulo of factorial[]

void prepare() // O( mod + log(mod) )
{
  f[0] = 1;
  for(int i = 1;i<mod;i++)f[i] = f[i-1] * i % mod;
  invf[mod-1] = bin_pow(f[mod-1],mod-2,mod);
  for(int i = mod-2;i;i--)invf[i] = invf[i+1] * (i + 1) % mod;
}

ll nCk(ll n,ll k) // O( 1 )
{
  return f[n] * invf[k] % mod * invf[n-k] % mod; // = f[n] / f[k] % mod / f[n-k] % mod
}
//End nCk code

//Lucas nCk code
ll nCk_lucas(ll n,ll k) // O( log_mod(n) )
{
  ll ans = 1;
  while(n)
  {
    ans = ans * nCk(n%mod,k%mod) % mod; // Lucas theorem
    n/=mod;
    k/=mod;
  }
  return ans;
}
//End Lucas nCk code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}