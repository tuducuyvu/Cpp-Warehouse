//Prime sieve
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

  // Marks all non-prime numbers in not_prime[]
void sieve_is_prime() // O( n * log(n) )
{
  not_prime[0] = not_prime[1] = 1;//   1 = true
  for(ll i = 2;i<maxn;i++)
  {
    if(!not_prime[i]) // i is prime
    {
      // Mark all multiples of i as not prime
      for(ll j = i * i;j<maxn;j+=i)not_prime[j] = 1;
    }
  }
}
//End Prime sieve code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    sieve_is_prime();
    
    
    return 0;
}