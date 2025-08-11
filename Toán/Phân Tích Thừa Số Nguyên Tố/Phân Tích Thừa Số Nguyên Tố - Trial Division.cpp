// Small Prime Factor
/* documents
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

// Small Prime Factor code
void trial_division(ll n) // O( sqrt(n) )
{
  if(n < 2)return;
  for(int k : {2,3,5})// Remove small primes first
  {
    while(n % k == 0)
    {
      cout<<k<<' ';
      n/=k;
    }
  }
  int i = 0;
  const int next[] = {4,2,4,2,4,6,2,6};
  // check for larger prime factors using 6k +/- 1 wheel
  for(ll k = 7;k*k <= n;k+=next[i++],i%=8)
  {
    while(n % k == 0)
    {
      cout<<k<<' ';
      n/=k;
    }
  }
  if(n>1)cout<<n<<' '; // remaining n is prime
}
//End Small Prime Factor code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}