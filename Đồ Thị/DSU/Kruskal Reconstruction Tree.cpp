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
const int maxlog = 20;

// Kruskal Reconstruction Tree Code
vector<int> adj[maxn]; // KRT

int root[maxn]; // DSU root

int N; // current node count of KRT

  // Initialize DSU
void prepare_DSU(int n)
{
    N = n;
    for(int i = 1;i<=n*2;i++)root[i] = i;
}

  // DSU find ( path compression )
int fi(int i)
{
    while(i != root[i])i = root[i] = root[root[i]];
    return i;
}

int ans[maxn]; // stores the edge index (or value) for each internal node
int p[maxn][maxlog], in[maxn],timer;
bool c[maxn];

  // Merge two sets using a new internal node representing the union
void unite(int u,int v,int val)
{
    u = fi(u);
    v = fi(v);
    if(u == v)return;
    ++N;
    adj[N].pb(u);
    adj[N].pb(v);
    root[u] = root[v] = p[u][0] = p[v][0] = p[N][0] = N;
    ans[N] = val;
}

void dfs(int i)
{
    in[i] = ++timer;
    c[i] = 1;
    for(int j = 1;j<maxlog;j++) p[i][j] = p[p[i][j-1]][j-1];
    
    for(int k : adj[i]) dfs(k);
}

  // Prepare LCA structures by running DFS and decomposition for each component
void prepare_LCA()
{
    for(int i = N; i; i--) // we iterate from N to ensure we start from the roots of the forest
        if(!c[i])dfs(i); 
}

  // Find LCA in the KRT
int lca(int u,int v)
{
    if(fi(u) != fi(v))return 0; // not in the same component
    if(u==v)return u;
    if(in[u] > in[v]) swap(u,v);
    for(int j = maxlog-1;j>=0;j--)
        if(p[v][j] && in[u] < in[p[v][j]] )  v = p[v][j];
    
    return p[v][0];
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
