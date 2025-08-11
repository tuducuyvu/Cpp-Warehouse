//Max Flow - Capacity Scaling (optimised)
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
 
//Max Flow - Capacity Scaling (optimised) code
struct Edge
{
  int u,v;
  pii edge[2];
  // Returns true if i is v (to select forward/reverse edge)
  bool find_edge(int i)const 
  {
    return i == v;
  }
  // Given a node, returns the other node of the edge
  int find_node(int i)const
  {
    if(i == u)return v;
    return u;
  }
};
vector<Edge> edges;
 
void add_edge(int u,int v,int w) // O( 1 )
{
  adj[u].pb(edges.size());
  adj[v].pb(edges.size());
  edges.pb({u,v,{mk(0,w),mk(0,0)}}); // edge[0] is forward, edge[1] is reverse
}
 
int cnt[maxn],t;
int require = INT_MAX;

  // DFS to find augmenting path with available capacity >= require
int dfs(int i,int e,int mn) // O( m )
{
  if(i == e)return mn;
  cnt[i] = t;
  for(int id : adj[i])
  {
    int k = edges[id].find_node(i); // Get the other node of the edge
    if(cnt[k] == t)continue;
    bool c = edges[id].find_edge(i); // Direction: forward or backward
    if(edges[id].edge[c].se - edges[id].edge[c].fi >= require)
    {
      int tmp = dfs(k,e,min(mn,edges[id].edge[c].se - edges[id].edge[c].fi));
      if(tmp)
      {
        edges[id].edge[c].fi += tmp;      // Update flow
        edges[id].edge[!c].fi -= tmp;     // Update reverse flow
        return tmp;
      }
    }
  }
  return 0;
}
 
ll max_flow(int s,int e) // O( m ^ 2 * log(require) )
{
  ll ans = 0;
  int tmp;
  // Iteratively decrease 'require' to find all possible flows
  for(;require;require>>=1)
  {
    while(++t,tmp = dfs(s,e,INT_MAX))ans+=tmp; // Send as much flow as possible at current scaling
  }
  return ans;
}
//End Max Flow - Capacity Scaling (optimised) code
 
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
    
    cout<<max_flow(1,n); // Output the maximum flow from node 1 to n
    
    return 0;
}