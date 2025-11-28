// DP Divide and Conquer 
/* documents
  https://wiki.vnoi.info/vi/algo/dp/dpdnc
  https://usaco.guide/plat/DC-DP?lang=cpp
  https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html
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

const int maxn = 3e3 + 10;
const ll inf = 1e17;

//Dp DnC Code
ll dp[2][maxn], cost[maxn][maxn];
bool now,pre;

void solve(int l,int r,int tl,int tr) // O( n*log(n) ) amortized
{
    if(l>r)return;
    int mid = (l + r)/2;
    
    dp[now][mid] = inf;
    int id = -1;
    for(int i = tl;i<=min(mid,tr);i++)
    {
        ll tmp = dp[pre][i-1] + cost[i][mid];
        if(dp[now][mid] > tmp)
        {
            dp[now][mid] = tmp;
            id = i;
        }
    }
    assert(id!=-1); // Just checking
    solve(l,mid-1,tl,id);
    solve(mid+1,r,id,tr);
}
//End Dp DnC Code

ll a[maxn], pf[maxn];

ll get_range(int l,int r) { return pf[r] - pf[l] - (a[r]-a[l])*l; }

ll cal(int l,int r,int mid)
{
    l--;
    return get_range(mid,r) +  (a[mid] - a[l]) * (mid-l) - get_range(l,mid);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/2087
    
    int n,k;
    cin>>n>>k;
    
    for(int i = 1;i<=n;i++)
    {
        cin>>a[i];
        pf[i] = a[i] * i + pf[i-1];
        a[i] += a[i-1];
        dp[now][i] = inf;
    }
    
    // Precompute costs ( optional )
    for(int l = 1;l<=n;l++)
    {
        int ptr = l;
        for(int r = l;r<=n;r++)
        {
            while(ptr<r && cal(l,r,ptr) > cal(l,r,ptr+1))ptr++;
            cost[l][r] = cal(l,r,ptr);
        }
    }
    
    // DP DnC   , O( k * n*log(n) )
    while(k--)
    {
        now = !now; // rolling array
        pre = !now;
        solve(1,n,1,n);
    }
    
    cout<<dp[now][n];
    
    return 0;
}