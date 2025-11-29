// DP Knuth's Optimization
/* documents
  https://cp-algorithms.com/dynamic_programming/knuth-optimization.html
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

const int maxn = 1e3 + 10;
int a[maxn];

//Dp Knuth's Optimization Code
ll dp[maxn][maxn];
int opt[maxn][maxn];

int cost(int l,int r)
{
    /* Cost function that satisfy 2 contidion with the following a<=b<=c<=d
        cost(b,c) <= cost(a,d)                           <monotony of expansion>
        cost(a,c) + cost(b,d) <= cost(a,d) + cost(b,c)   <quadrangle inequality>
    */
    return a[r] - a[l-1];
}

bool solve()
{
    int s,n;
    if(cin>>s>>n);
    else return 0;
    
    for(int i = 1;i<=n;i++) cin>>a[i];
    a[++n] = s;
    
    for(int i = 1;i<=n;i++) // base case
    {
        dp[i][i] = 0;
        opt[i][i] = i;
    }
      // O( n^2 )
    for(int len = 2;len<=n;len++)
    {
        for(int l = 1,r = len; r<=n; l++,r++)
        {
            dp[l][r] = LLONG_MAX;
            
            for(int k = opt[l][r-1]; k <= min(r-1, opt[l+1][r] ); k++)
            {
                ll tmp = dp[l][k] + dp[k+1][r] + cost(l,r);
                if(dp[l][r] >= tmp)
                {
                    dp[l][r] = tmp;
                    opt[l][r] = k;
                }
            }
        }
    }
    
    
    cout<<dp[1][n]<<'\n';
    return 1;
}
//End Dp Knuth's Optimization Code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://www.spoj.com/problems/BRKSTRNG/
    
    while(solve());
    
    return 0;
}
