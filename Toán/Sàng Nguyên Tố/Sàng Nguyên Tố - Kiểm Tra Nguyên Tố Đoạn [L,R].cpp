//Prime sieve range
/* documents
https://wiki.vnoi.info/vi/algo/algebra/prime_sieve
https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
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

const int maxn = 1e6 + 10;

//Prime sieve code
bool not_prime[maxn];
vector<int> primes;
  // Computes all primes up to maxn and marks non-primes in not_prime[]
void sieve_is_prime() // O( n * log(n) )
{
  not_prime[0] = not_prime[1] = 1;//   1 = true
  for(ll i = 2;i<maxn;i++)
  {
    if(!not_prime[i])
    {
      primes.pb(i); // Store the prime number
      // Mark all multiples of i as not prime
      for(ll j = i * i;j<maxn;j+=i)not_prime[j] = 1;
    }
  }
}
//End Prime sieve code

//Prime sieve range code
bool not_range_prime[maxn];
  // Marks non-primes in [l, r] using precomputed primes
void sieve_range(ll l,ll r) // O( range * log(range) + sqrt(r) ) ,  r <= 1e12  (!)
{
  for(ll k : primes)
  {
    if(k * k > r)break;
    // Start marking from the max of k*k or the first multiple of k >= l
    ll i = max(k * k, l - l % k);
    if(i < l)i+=k;
    
    for(;i<=r;i+=k)
    {
      not_range_prime[i-l] = 1; // Mark as not prime in the range
    }
  }
}
//End Prime sieve range code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    sieve_is_prime(); // Precompute primes up to maxn
    
    //example
    sieve_range(10,100); 
    for(int i = 10;i<=100;i++)
    {
      cout<<i<<' '<<not_range_prime[i-10]<<'\n';
    }
    
    return 0;
}