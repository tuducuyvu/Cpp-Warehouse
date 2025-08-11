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
int small_prime_divisor[maxn];
  // Fills small_prime_divisor[] with the smallest prime divisor for each number
void sieve_prime_divisor() // O( n * log(n) )
{
  small_prime_divisor[0] = small_prime_divisor[1] = 0;
  
  for(ll i = 2;i<maxn;i++)
  {
    if(small_prime_divisor[i] == 0)
    {
      small_prime_divisor[i] = i; // i is prime, so its smallest prime divisor is itself
      for(ll j = i * i;j<maxn;j+=i)  
      {
        if(small_prime_divisor[j]==0) 
        {
          small_prime_divisor[j] = i; // Mark first (smallest) prime divisor for j
        }
      }
    }
  }
}
//End prime sieve code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    sieve_prime_divisor(); 
    
    
    return 0;
}