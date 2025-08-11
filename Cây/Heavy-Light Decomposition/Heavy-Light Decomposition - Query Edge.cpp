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
vector<pii> adj[maxn]; // Đồ Thị (Graph adjacency list)
int edge[maxn];

//Segment tree 2*n code
int n;
ll t[maxn * 2 + 10];//segment tree

void build() // O( n )
{
  // Build internal nodes (bottom-up)
  for(int i = n-1; i; i--) 
    t[i] = max(t[i*2] , t[i*2+1]);
}

// Update value at position i to val
void up(int i, int val) // O( log(n) )
{
  i += n; // Move to leaf position
  t[i] = val;
  // Update all ancestors of i
  for(; i > 1; i >>= 1)
    t[i>>1] = max(t[i] , t[i^1]);
}

  // Calculate max on interval [l, r-1]   (!) its r-1, not r
ll cal(int l, int r) // O( log(n) )
{
  ll ans = 0;
  l += n; // Move to leaf
  r += n; // Move to leaf
    // Traverse up, collecting segments covering [l, r-1]
  for(; l < r; l >>= 1, r >>= 1)
  {
    if(l & 1) ans = max(t[l++],ans); // If l is right child, use it then move to next
    if(r & 1) ans = max(t[--r],ans); // If r is right child, use the previous left child
  }
  return ans;
}
//End Segment tree 2*n code

//HLD code
int depth[maxn],tim[maxn],heavy[maxn],head[maxn],p[maxn],tt;
int represent[maxn];

  // DFS calculates subtree sizes to find heavy child :)
int dfs(int i,int pa) // O( n )
{
  int S = 1;         // Size of subtree rooted at i
  int max_s = 0;     // Size of the largest child subtree
  p[i] = pa;         // Parent of i
  depth[i] = depth[pa] + 1; // Depth of i
  for(pii k : adj[i])
  {
    if(k.fi == pa)continue;
    int s = dfs(k.fi,i); 
    S += s;
    represent[k.se] = k.fi; // represent each edge with a node as we perform DFS
    if(s > max_s)
    {
      max_s = s;
      heavy[i] = k.fi;   // Heavy child is the one with largest subtree
    }
  }
  return S;
}

  // Decompose tree into heavy chains
void decompose(int i,int h) // O( n )
{
  head[i] = h;         // Head of current heavy chain
  tim[i] = ++tt;        // Time index for node i (needed for Fenwick)
  if(heavy[i])decompose(heavy[i],h); // Continue heavy chain
  for(pii k : adj[i])
  {
    if(k.fi == p[i] || k.fi == heavy[i])continue;
    decompose(k.fi,k.fi);    // Start new heavy chain for light child
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

  // Get path max from u up to v (where u is deeper)
ll jump_path(int u,int v) // O( log(n) )
{
  ll ans = 0;
  while(depth[u] > depth[v])
  {
    int h = head[u];
    if(depth[h] <= depth[v])
    {
      ans = max(ans,cal(tim[v]+1,tim[u]+1)); // Add segment of the last heavy chain
      // we exclude v out of the segment because we dont need the edge that node v represent ( outside of our path )
      break;
    }
    else 
    {
      ans = max(ans,cal(tim[h],tim[u]+1)); // Add segment of the current heavy chain
      u = p[h]; // change heavy chain
    }
  }
  return ans;
}

  // Get max of values on the path  u to v
ll solve_path(int u,int v) // O( log(n) )
{
  int g = lca(u,v);
  return max(jump_path(u,g) , jump_path(v,g)); // max of both sides
}
//End HLD code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://www.spoj.com/problems/QTREE/
    // uoc j
    
    int T;
    cin>>T;
    while(T--)
    {
      cin>>n;
      for(int i = 1;i<=n;i++)
      {
        adj[i].clear();
        depth[i] = heavy[i] = head[i] = tim[i] = p[i] =  0;
      }
      for(int i = 1;i<=n*2;i++)
      {
        t[i] = 0;
      }
      for(int i = 1;i<n;i++)
      {
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].pb(mk(v,i)); // pair of (node, id_of_edge)
        adj[v].pb(mk(u,i));
        edge[i] = w;
      }
      tt = 0;
      dfs(1,0); // prepare for decompose
      decompose(1,1); // decompose
      //decompose decompose
      //decompose decompose decompose decompose
      
      for(int i = 1;i<n;i++)t[tim[represent[i]] + n] = edge[i]; // every edge is represented by a node, so now this is just HLD on Node
      build();
      
      string s;
      while(cin>>s)
      {
        if(s == "DONE")break;
        if(s == "CHANGE")
        {
          int u,w;
          cin>>u>>w;
          up(tim[represent[u]],w); 
        }
        else
        {
          int u,v;
          cin>>u>>v;
          cout<<solve_path(u,v)<<'\n'; 
        }
      }
    }
      
    return 0;
}