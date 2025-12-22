// 2-Vertex Connected Component ( aka Biconnected Components)
/* documents
  https://usaco.guide/adv/BCC-2CC
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

const int maxn = 1e5 + 10;
vector<int> adj[maxn];

// Biconnected Component code
int tim[maxn],low[maxn],com[maxn];
int t,com_cnt;
bool crit[maxn]; // articulation point marker
stack<int> st;
vector<int> bcc[maxn]; // stores biconnected components
vector<int> com_adj[maxn * 2]; // compressed graph adjacency ( Block-cut Tree )

void dfs(int i,int pa)
{
    tim[i] = low[i] = ++t; // set discovery and low times
    int child = 0;         // count children for root
    st.push(i);            // push current node onto stack
    for(int k : adj[i])
    {
        if(k == pa)continue; 
        if(tim[k])low[i] = min(low[i],tim[k]); 
        else
        {
            dfs(k,i); 
            low[i] = min(low[i],low[k]); 
            child++;
            if(pa == 0 && child >= 2)crit[i] = 1;            // articulation that is also root
            if(pa && low[k] >= tim[i])crit[i] = 1;           // articulation by low-link
      
              // If subtree can't reach ancestor, pop stack for new BCC
            if(low[k] >= tim[i])
            {
                com_cnt++;
                while(st.top() != k)
                {
                    bcc[com_cnt].pb(st.top());
                    st.pop();
                }
                bcc[com_cnt].pb(st.top());
                st.pop();
                
                bcc[com_cnt].pb(i);
            }
        }
    }
}

  // Build a compressed block-cut tree from BCCs and articulation points
void compress_graph(int n)
{
    for(int i = 1;i<=com_cnt;i++)
    {
        for(int k : bcc[i])
        {
            if(crit[k])
            {
                com[k] = k; // make articulation point its own component
                com_adj[n + i].pb(k); // connect articulation to BCC node
                com_adj[k].pb(n + i);
            }
            else com[k] = n + i; // assign component ID for non-articulation
        }
    }
}
// End Biconnected component Code

namespace LCA
{
    const int maxlog = 20;
    int in[maxn * 2],p[maxn * 2][maxlog],t;
    
    void dfs(int i,int pa) 
    {
        in[i] = ++t;
        p[i][0] = pa;
        for(int j = 1;j<maxlog;j++)p[i][j] = p[p[i][j-1]][j-1];
        for(int k : com_adj[i])
        {
            if(k==pa)continue;
            dfs(k,i);
        }
    }
    
    int lca(int u,int v) 
    {
        if(u==v)return u;
        if(in[u]>in[v])swap(u,v);
        for(int j = maxlog-1;j>=0;j--)
        {
            if(p[v][j] && in[u] < in[p[v][j]])v = p[v][j];
        }
        return p[v][0];
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/1705
    
    int n,m,q;
    cin>>n>>m>>q;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        adj[u].pb(v); 
        adj[v].pb(u); 
    }
    
    dfs(1,0); // find BCCs and articulation points
    if(st.size() > 1)
    {
        com_cnt++;
        for(;st.size();st.pop()) bcc[com_cnt].pb(st.top()); // handle leftovers
    }
    
    compress_graph(n); // build block-cut tree
    
    LCA::dfs(com[1],0); 
    
    while(q--)
    {
        int a,b,c;
        cin>>a>>b>>c;
          
        if(a == c || b == c)
        {
            cout<<"NO\n";
            continue;
        }
        
        if(!crit[c])
        {
            cout<<"YES\n"; 
            continue;
        }
        
        a = com[a];
        b = com[b];
        c = com[c];
        
        if(a == c || b == c)
        {
            cout<<"YES\n";
            continue;
        }
        
        int l = LCA::lca(a,b);
        int la = LCA::lca(a,c);
        int lb = LCA::lca(b,c);
        
          // Check if c is on the path between a and b in the block-cut tree
        if(l == c || (la == c && lb == l) || (lb == c && la == l))cout<<"NO\n";
        else cout<<"YES\n";
        
    }
    
    return 0;
}
