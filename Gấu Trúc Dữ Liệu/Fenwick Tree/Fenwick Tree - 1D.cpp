//Fenwick 1D
/* documents
https://wiki.vnoi.info/algo/data-structures/fenwick
https://cp-algorithms.com/data_structures/fenwick.html
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

//Fenwick 1D code
ll bit[maxn];

  // add val to I-th element
void up(int I,int val)  //  O( log(n) )
{
  for(int i = I;i<maxn;i+=i&-i)bit[i] += val;
}

  // calculate sum of prefix [1..I]
ll cal(int I)  // O( log(n) )
{
  ll ans = 0;
  for(int i = I;i;i-=i&-i)ans += bit[i];
  return ans;
}

  //range sum from l to r
ll range(int l,int r)  // O( log(n) )
{
  return cal(r) - cal(l-1);
}
//End Fenwick 1D code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}