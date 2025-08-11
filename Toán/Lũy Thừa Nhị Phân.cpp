// bin_pow
/* documents
https://wiki.vnoi.info/vi/algo/algebra/binary_exponentation
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    // (3 * 4) % 5
    cout<<bin_mul(3,4,5)<<'\n';
    
    // (3 mũ 4) % 5
    cout<<bin_pow(3,4,5)<<'\n';
    
    // (3410411074017137 mũ 419197317294691) % 10000000000000007
    cout<<bin_pow_large_mod(3410411074017137,419197317294691,10000000000000007)<<'\n';
    
    return 0;
}