//Sparse Table
/* documents
  https://cp-algorithms.com/data_structures/sparse-table.html
  https://wiki.vnoi.info/vi/algo/data-structures/rmq
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
 
const int maxn = 2e5 + 10,maxlog = 20;
 
//Code Sparse Table
int table[maxn*2][maxlog];
 
void build(const vector<int> & v) // O( n*log(n) )
{
    int n = v.size();
    for(int i = 0;i<n;i++)table[i][0] = v[i];
    for(int t = 1;(1<<t) <= n;t++)
        for(int i = 0;i <= n-(1<<t);i++)
            table[i][t] =  min(table[i][t-1] , table[i+(1<<t-1)][t-1]) ;
}
 
  // Query minimum value in range [l,r] using sparse table
int get(int l,int r) // O( 1 )
{
    int lg = 31 - __builtin_clz( r - l + 1);
    return min(table[l][lg], table[r - (1<<lg)+1][lg]);
}
 
  // Alternative method to get ans in range [l,r] 
int get_precise(int l,int r) // O( maxlog )
{
    int ans = INT_MAX;
    for(int t = maxlog-1; t>=0 && l<=r;t--)
    {
        if(l+(1<<t)-1<=r)
        {
            ans = min(ans,table[l][t]);
            l += (1<<t);
        }
    }
    return ans;
}
//End Code Sparse Table
 
 
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/1688
    
    int n,m;
    cin>>n>>m;
    
    vector<int> a(n);
    for(int i = 0;i<n;i++)cin>>a[i];
    
    build(a);  // Build sparse table
    
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        cout<< get(u-1,v-1)<<'\n';
    }
    
    return 0;
}
