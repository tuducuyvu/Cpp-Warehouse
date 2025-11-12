// LCA
/* documents
  https://wiki.vnoi.info/vi/algo/data-structures/lca
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

const int maxn = 2e5 + 10,maxlog = 19;

vector<int> adj[maxn];


namespace LCA_binlift
{
    int d[maxn],p[maxn][maxlog];
    
    void dfs(int i,int pa) // O( n * maxlog )
    {
          // Initialize depth and binary lifting table
        d[i] = d[pa]+1;
        p[i][0] = pa;
        for(int j = 1;j<maxlog;j++) p[i][j] = p[p[i][j-1]][j-1]; 
        for(int k : adj[i])
        {
            if(k==pa)continue;
            dfs(k,i);
        }
    }
    
    void lift(int &i,int tmp) // O( maxlog )
    {
        for(int j = maxlog-1;j>=0;j--)
        {
            if(tmp >= (1<<j)) 
            {
                i = p[i][j];
                tmp -= (1<<j);
            }
        }
    }
    
    int lca(int u,int v) // O( maxlog )
    {
        if(d[u]<d[v])swap(u,v);
        lift(u,d[u]-d[v]); // Bring nodes to same depth
        if(u==v)return u;
        for(int j = maxlog-1;j>=0;j--)
        {
            if(p[u][j] != p[v][j])
            {
                u = p[u][j];
                v = p[v][j];
            }
        }
        return p[u][0];
    }
}

namespace LCA_eulertour
{
    int in[maxn],p[maxn][maxlog],t;
    
    void dfs(int i,int pa) // O( n * maxlog )
    {
          // Record entry time and build parent table
        in[i] = ++t;
        p[i][0] = pa;
        for(int j = 1;j<maxlog;j++)p[i][j] = p[p[i][j-1]][j-1];
        for(int k : adj[i])
        {
            if(k==pa)continue;
            dfs(k,i);
        }
    }
    
    int lca(int u,int v) // O( maxlog )
    {
          // LCA using Euler Tour in-time comparison
        if(u==v)return u;
        if(in[u]>in[v])swap(u,v);
        for(int j = maxlog-1;j>=0;j--)
        {
            if(p[v][j] && in[u] < in[p[v][j]])v = p[v][j];
        }
        return p[v][0];
    }
}

namespace LCA_HLD
{
    int heavy[maxn],head[maxn],p[maxn],d[maxn];
    int dfs(int i,int pa) // O( n )
    {
          // Find heavy child and subtree sizes
        p[i] = pa;
        d[i] = d[pa]+1;
        int S = 1,mx = 0;
        for(int k : adj[i])
        {
            if(k==pa)continue;
            int s = dfs(k,i);
            S += s;
            if(s>mx)
            {
                mx = s;
                heavy[i] = k; 
            }
        }
        return S;
    }
    void decompose(int i,int h) // O( n )
    {
          // Decompose tree into chains
        head[i] = h;
        if(heavy[i])decompose(heavy[i],h); // Continue heavy chain
        for(int k : adj[i])
        {
            if(k != p[i]  && k != heavy[i])decompose(k,k); // New light chain
        }
    }
    
    void build() // O( n )
    {
        dfs(1,0);
        decompose(1,1);
    }
    
    int lca(int u,int v) // O( log(n) )
    {
          // Move up chains until common head
        while(head[u] != head[v])
        {
            int U = p[head[u]],V = p[head[v]];
            if(d[U] >= d[V]) u = U;
            if(d[V] >= d[U]) v = V;
        }
        return (d[u]<d[v]?u:v);
    }
}

namespace LCA_RMQ
{
    int table[maxn*2][maxlog], id[maxn * 2],in[maxn];
    vector<int> tour;
    
    void dfs(int i,int p) // O( n )
    {
          // Create Euler Tour and record positions
        in[i] = tour.size();
        id[in[i]] = i;
        tour.pb(in[i]);
        
        for(int k : adj[i])
        {
            if(k==p)continue;
            dfs(k,i);
            tour.pb(in[i]); // Add parent after subtree
        }
    }
    
    void build() // O( n * log(n) )
    {
        dfs(1,0);
        int n = tour.size();
          // Build sparse table for RMQ
        for(int i = 0;i<n;i++)table[i][0] = tour[i];
        
        for(int sz = 1;(1<<sz) <= n;sz++)
            for(int i = 0;i<=n-(1<<sz);i++)
                table[i][sz] = min(table[i][sz-1],table[i+(1<<sz-1)][sz-1]);
    }
    
    int get(int l,int r) // O( 1 )
    {
          // Range minimum query using sparse table
        int lg = 31- __builtin_clz(r-l+1);
        return min(table[l][lg],table[r-(1<<lg)+1][lg]);
    }
    
    int lca(int u,int v) // O( 1 ) 
    {
          // Find minimum in tour range and map to node
        if(in[u] > in[v])swap(u,v);
        return id[get(in[u],in[v])];
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/1688
    
    int n,m;
    cin>>n>>m;
    
    for(int i = 2;i<=n;i++)
    {
        int x;
        cin>>x;
        adj[x].pb(i);
        adj[i].pb(x);
    }
    /*
    LCA_binlift::dfs(1,0);
    LCA_eulertour::dfs(1,0);
    LCA_HLD::build();
    */
    LCA_RMQ::build();
    
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        cout<<LCA_RMQ::lca(u,v)<<'\n';
    }
    
    return 0;
}
