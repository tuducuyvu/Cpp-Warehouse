//HLD 
/* documents
https://cp-algorithms.com/graph/hld.html
https://wiki.vnoi.info/algo/data-structures/heavy-light-decomposition
https://usaco.guide/plat/hld
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

const int maxn = 2e5 + 10;
vector<int> adj[maxn]; // Đồ Thị (Graph adjacency list)
int a[maxn];

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

//HLD code
int depth[maxn],tim[maxn],heavy[maxn],head[maxn],p[maxn],t;

  // DFS calculates subtree sizes to find heavy child :)
int dfs(int i,int pa) // O( n )
{
  int S = 1;         // Size of subtree rooted at i
  int max_s = 0;     // Size of the largest child subtree
  p[i] = pa;         // Parent of i
  depth[i] = depth[pa] + 1; // Depth of i
  for(int k : adj[i])
  {
    if(k == pa)continue;
    int s = dfs(k,i); 
    S += s;
    if(s > max_s)
    {
      max_s = s;
      heavy[i] = k;   // Heavy child is the one with largest subtree
    }
  }
  return S;
}

  // Decompose tree into heavy chains
void decompose(int i,int h) // O( n )
{
  head[i] = h;         // Head of current heavy chain
  tim[i] = ++t;        // Time index for node i (needed for Fenwick)
  if(heavy[i])decompose(heavy[i],h); // Continue heavy chain
  for(int k : adj[i])
  {
    if(k == p[i] || k == heavy[i])continue;
    decompose(k,k);    // Start new heavy chain for light child
  }
}

  // Find LCA using HLD
int lca(int u,int v) // O( log(n) )
{
  while(head[u] != head[v]) // not in same heavy chain
  {
    int U = p[head[u]],V = p[head[v]]; // the position in the next chain if u/v change chain
    if(depth[U] >= depth[V])u = U; // u not reached v
    if(depth[V] >= depth[U])v = V; // v not reached u
  }
  return (depth[u] < depth[v]?u:v); // Return the node with lower depth
}

  // Get path sum from u up to v (where u is deeper or equal)
ll jump_path(int u,int v) // O( log(n) )
{
  ll ans = 0;
  while(depth[u] >= depth[v])
  {
    int h = head[u];
    if(depth[h] <= depth[v])
    {
      ans += range(tim[v],tim[u]); // Add segment of the last heavy chain
      break;
    }
    else 
    {
      ans += range(tim[h],tim[u]); // Add segment of the current heavy chain
      u = p[h]; // change heavy chain
    }
  }
  return ans;
}

  // Get sum of values on the path  u to v
ll solve_path(int u,int v) // O( log(n) )
{
  int g = lca(u,v);
  return jump_path(u,g) + jump_path(v,g) - a[g]; // Sum up both sides, subtract duplicate value at LCA
}
//End HLD code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    //https://cses.fi/problemset/task/1138
    // we use HLD to solve this problem lmao
    
    int n,q;
    cin>>n>>q;
    for(int i = 1;i<=n;i++)cin>>a[i]; 
    for(int i = 1;i<n;i++)
    {
      int u,v;
      cin>>u>>v;
      adj[u].pb(v);
      adj[v].pb(u);
    }
    dfs(1,0); // prepare for decompose
    decompose(1,1); // decompose
    //decompose
    //decompose
    
    for(int i = 1;i<=n;i++)up(tim[i],a[i]); // (!) update at tim[i], not i
    
    while(q--)
    {
      int i;
      cin>>i;
      if(i == 1)
      {
        int u,w;
        cin>>u>>w;
        up(tim[u],w - a[u]); // (!) update at tim[u], not u
        a[u] = w;
      }
      else
      {
        int u;
        cin>>u;
        cout<<solve_path(u,1)<<'\n'; 
      }
    }
    return 0;
}