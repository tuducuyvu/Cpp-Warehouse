// Discrete Logarithm - Baby Step/Giant Step
/*
  https://cp-algorithms.com/algebra/discrete-log.html
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

//Code Discrete Logarithm - Baby Step/Giant Step 
  // Solve discrete log equation: find x such that k*a^x ≡ b (modulo mod)
  // Baby Step/Giant Step algorithm
ll find_sol(ll a,ll b,ll mod,ll k = 1)// O( sqrt(mod) )
{
  a %= mod; 
  b %= mod; 
  ll n = sqrt(mod) + 1; 

  unordered_map<ll,int> mp; // Store baby steps

  mp[b] = 0;
  ll cur = 1;
  
  for(int i = 1;i<=n;i++)
  {
    cur = cur * a % mod; // Compute a^i modulo mod
    mp[cur * b % mod] = i; // Store value for lookup in giant steps
  }
  
  ll step = cur; // Giant Step = a^n
  cur = k; // Start with offset k
  
  for(int i = 1;i<=n;i++)
  {
    cur = cur * step % mod; // Compute k*(a^n)^i modulo mod
    if(mp.count(cur)) return n * i - mp[cur]; // If found, return solution
  }
  return -1; // No solution found
}

  // Handles edge cases with GCD reduction, then solves discrete log
ll discrete_log(ll a,ll b,ll mod) // O( sqrt(mod) )
{
  a %= mod;
  b %= mod; 
  
  ll k = 1, add = 0, g;
  
    // Reduce problem by factoring out GCDs of 'a' and 'mod'
  while( (g = __gcd(a,mod)) > 1)
  {
    if(b == k)return add; // Solution found in GCD reduction
    if(b % g) return -1; // No solution if b not divisible by GCD
    b /= g;
    mod /= g;
    k = k * a / g % mod;
    add++; // Update offset
  }
  
  ll ans = find_sol(a,b,mod,k); // Use baby-step giant-step to solve 
  if(ans != -1) ans += add; // Add offset to final answer if solution found
  return ans; // Return solution or -1 if not found
}
//End Code Discrete Logarithm - Baby Step/Giant Step

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://www.spoj.com/problems/MOD
    
    ll a,b,mod;
    while(cin>>a>>mod>>b)
    {
      if(mod == 0)return 0;
      
      ll ans = discrete_log(a,b,mod); 
      
      if(ans == -1)cout<<"No Solution"<<'\n'; 
      else cout<<ans<<'\n'; 
    }
    
    return 0;
}