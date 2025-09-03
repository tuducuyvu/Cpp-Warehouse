//  Kruskal Reconstruction Tree ( KRT )
/* documents
  https://usaco.guide/plat/kruskal-tree?lang=cpp
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

const int maxn = 4e5 + 10; // = n * 2

// Kruskal Reconstruction Tree Code
vector<int> adj[maxn]; // adjacency list for tree structure

int root[maxn]; // DSU root array

int head[maxn], heavy[maxn], d[maxn], p[maxn]; // HLD things

int N; // current node count in the virtual tree ( KRT )

  // Initialize DSU and parent arrays
void prepare_DSU(int n)
{
    N = n;
    for(int i = 1;i<=n*2;i++)root[i] = i;
}

  // DSU find with path compression
int fi(int i)
{
    while(i != root[i])i = root[i] = root[root[i]];
    return i;
}

int ans[maxn]; // stores the edge index (or value) for each virtual node

  // Merge two sets using a new virtual node representing the union
void unite(int u,int v,int val)
{
    u = fi(u);
    v = fi(v);
    if(u == v)return;
    ++N;
    adj[N].pb(u);
    adj[N].pb(v);
    root[u] = root[v] = p[u] = p[v] = p[N] = N;
    ans[N] = val;
}

  // DFS to find the heavy child for HLD
int dfs(int i)
{
    int S = 1, mx = 0;
    for(int k : adj[i])
    {
        d[k] = d[i]+1; // set depth
        int s = dfs(k); // subtree size
        S += s;
        if(s > mx)
        {
            mx = s;
            heavy[i] = k; // set heavy child
        }
    }
    return S;
}
 
  // Decompose the tree for HLD, setting head for each chain
void decompose(int i,int h)
{
    head[i] = h;
    if(heavy[i])decompose(heavy[i],h); // continue heavy path
    for(int k : adj[i])
    {
        if(k != heavy[i])decompose(k,k); // start new chain for light children
    }
}

  // Prepare LCA structures by running DFS and decomposition for each component
void prepare_LCA()
{
    for(int i = N; i; i--) // we iterate from N to ensure we start from the roots of the forest
    {
        if(!d[i])
        {
            dfs(i); // calculate sizes and heavy child
            decompose(i,i); // chain decomposition
        }
    }
}

  // Find LCA in the KRT using HLD chains
int lca(int u,int v)
{
    if(fi(u) != fi(v))return 0; // not in the same component
    while(head[u] != head[v])
    {
        int U = p[head[u]], V = p[head[v]];
        if(d[U]>=d[V])u = U;
        if(d[V]>=d[U])v = V;
    }
    return (d[u] < d[v]?u:v);
}

  // Get the value (edge index) at the LCA of u and v, or -1 if not connected
int get(int u,int v)
{
    int k = lca(u,v);
    if(k)return ans[k];
    else return -1;
}
// End Kruskal Reconstruction Tree Code
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/2101
    
    int n,m,q;
    cin>>n>>m>>q;
    
    prepare_DSU(n);
    
      // Add edges and build the virtual tree
    for(int i = 1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        unite(u,v,i);
    }
    
    prepare_LCA();
    
      // Answer the queries
    while(q--)
    {
        int u,v;
        cin>>u>>v;
        cout<<get(u,v)<<'\n';
    }
    
    return 0;
}