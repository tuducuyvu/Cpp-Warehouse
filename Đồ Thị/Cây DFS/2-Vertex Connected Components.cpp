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

//HLD code
namespace HLD 
{
    int depth[maxn * 2],heavy[maxn * 2],head[maxn * 2],p[maxn * 2];
    int dfs(int i,int pa) 
    {
        int S = 1;         
        int max_s = 0;     
        p[i] = pa;         
        depth[i] = depth[pa] + 1; 
        for(int k : com_adj[i])
        {
            if(k == pa)continue;
            int s = dfs(k,i); 
            S += s;
            if(s > max_s)
            {
                max_s = s;
                heavy[i] = k; 
            }
        }
        return S;
    }
    
    void decompose(int i,int h) 
    {
        head[i] = h;         
        if(heavy[i])decompose(heavy[i],h); 
        for(int k : com_adj[i])
        {
            if(k != p[i] && k != heavy[i])decompose(k,k);
        }
    }
    
    int lca(int u,int v) 
    {
        while(head[u] != head[v]) 
        {
            int U = p[head[u]],V = p[head[v]];
            if(depth[U] >= depth[V])u = U; 
            if(depth[V] >= depth[U])v = V;
        }
        return (depth[u] < depth[v]?u:v);
    }
}
// End HLD Code

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
    
      // the rest is to solve the problem
    HLD::dfs(com[1],0); 
    
    HLD::decompose(com[1],com[1]); 
    
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
        
        int l = HLD::lca(a,b);
        int la = HLD::lca(a,c);
        int lb = HLD::lca(b,c);
        
          // Check if c is on the path between a and b in the block-cut tree
        if(l == c || (la == c && lb == l) || (lb == c && la == l))cout<<"NO\n";
        else cout<<"YES\n";
        
    }
    
    return 0;
}