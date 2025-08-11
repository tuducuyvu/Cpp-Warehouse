// Max Flow - Capacity Scaling (easy implement)
/* documents
https://www.youtube.com/watch?v=1ewLrXUz4kk&t=10s&ab_channel=WilliamFiset
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

const int maxn = 2e3 + 10;
vector<int> adj[maxn];// Đồ Thị (Graph adjacency list)

// Max Flow - Capacity Scaling (easy implement) code
vector <pii> edge[maxn][maxn]; // pairs of ( used_cap , cap )
int cnt[maxn],t;
int require = INT_MAX;

void add_edge(int u,int v,int w)
{
  adj[u].pb(v);
  adj[v].pb(u);
  edge[u][v].pb(mk(0,w));//directed
  edge[v][u].pb(mk(0,0));// mk(0,w) here if undirected
}

  // Find an augmenting path from i to e with at least 'require' capacity.
int dfs(int i,int e,int mn)
{
  if(i == e)return mn;
  cnt[i] = t;
  for(int k : adj[i])
  {
    if(cnt[k] == t)continue;
    for(pii &l : edge[i][k])
    {
      if(l.se - l.fi >= require)
      {
        int tmp = dfs(k,e,min(mn,l.se-l.fi)); // Recursively search for more flow
        if(tmp)
        {
          l.fi += tmp;
          edge[k][i].begin()->fi -= tmp; // Update reverse edge
          return tmp;
        }
        break;
      }
    }
  }
  return 0;
}

  // compute max flow from s to e.
ll max_flow(int s,int e,int n) // O( m ^ 2 * log(require) )
{
  ll ans = 0;
  int tmp;
  for(;require;require>>=1)
  {
    while(++t,tmp = dfs(1,n,INT_MAX))ans+=tmp; // Try to send flow while possible
  }
  return ans;
}
//End Max Flow - Capacity Scaling (easy implement) code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    //https://cses.fi/problemset/task/1694
    int n,m;
    cin>>n>>m;
    while(m--)
    {
      int u,v,w;
      cin>>u>>v>>w;
      add_edge(u,v,w);
    }
    
    cout<<max_flow(1,n,n); // Output the maximum flow from node 1 to n
    
    return 0;
}