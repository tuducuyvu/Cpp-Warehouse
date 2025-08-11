//Fenwick 3D
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

const int maxn = 5e2 + 10;

//Fenwick 3D code
ll bit[maxn][maxn][maxn];

  // add val to coordinate (I,J,K) 
void up(int I,int J,int K,int val) // O( log(n) ^ 3 )
{
  for(int i = I;i<maxn;i+=i&-i)
  {
    for(int j = J;j<maxn;j+=j&-j)
    {
      for(int k = K;k<maxn;k+=k&-k)bit[i][j][k] += val;
    }
  }
}

  // calculate sum of 3D prefix ( [1..I] , [1..J] , [1..K] )
ll cal(int I,int J,int K)  //  O( log(n) ^ 3 )
{
  ll ans = 0;
  for(int i = I;i;i-=i&-i)
  {
    for(int j = J;j;j-=j&-j) 
    {
      for(int k = K;k;k-=k&-k)ans += bit[i][j][k];
    }
  }
  return ans;
}
//End Fenwick 3D code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}