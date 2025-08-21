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
ll edge[maxn][maxn]; // Capacity of edge u->v
int cnt[maxn],t;
ll require = LLONG_MAX;

void add_edge(int u,int v,int w)
{
  adj[u].pb(v);
  adj[v].pb(u);
  edge[u][v] += w;//directed
}

  // Find an augmenting path from i to e with at least 'require' capacity.
ll dfs(int i,int e,ll mn)
{
  if(i == e)return mn;
  cnt[i] = t;
  for(int k : adj[i])
  {
    if(cnt[k] == t)continue;
    
    if(edge[i][k] >= require)
    {
      ll tmp = dfs(k,e,min(mn,edge[i][k])); // Recursively search for more flow
      if(tmp)
      {
        edge[i][k] -= tmp; // Update edge
        edge[k][i] += tmp; // Update reverse edge
        return tmp;
      }
    }
  }
  return 0;
}

  // compute max flow from s to e.
ll max_flow(int s,int e,int n) // O( m ^ 2 * log(require) )
{
  ll ans = 0;
  ll tmp;
  for(;require;require>>=1)
  {
    while(++t,tmp = dfs(1,n,LLONG_MAX))ans+=tmp; // Try to send flow while possible
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
