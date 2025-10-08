// Virtual Tree
/* documents
  https://hackmd.io/@1OR5F5o5T_ahzGRzQ3ydZQ/H1zWG0DWT
  https://usaco.guide/plat/VT?lang=cpp
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

const int maxn = 2e5 + 10, maxlog = 18;
vector<int> adj[maxn]; // graph ( tree )

// Virtual Tree Code
vector<pii> com_adj[maxn]; // compressed tree for each query

int in[maxn],out[maxn]; // In-time and out-time
int depth[maxn],p[maxn][maxlog],timer;

  // Euler tour
void dfs(int i,int pa) // O( n * maxlog )
{
    depth[i] = depth[pa] + 1;
    
    p[i][0] = pa; 
    
    for(int j = 1; j<maxlog; j++) p[i][j] = p[p[i][j-1]][j-1];
    
    in[i] = ++timer;
    
    for(int k : adj[i])
    {
        if(k==pa)continue; 
        dfs(k,i); 
    }
    out[i] = timer; 
}
  
  // Comparator to sort nodes based on in-time
bool cmp(int a,int b)
{
    return in[a]<in[b]; 
}

  // Finds the Lowest Common Ancestor (LCA) of two nodes
int lca(int u,int v) // O( maxlog )
{
    if( in[u] > in[v] )swap(u,v); // Ensure 'v' is not the ancestor of 'u'
    
    for(int j = maxlog-1;j>=0;j--)
    {
        if( in[u] < in[p[v][j]] ) v = p[v][j]; 
    }
    
    return p[v][0]; // Return the LCA
}

  // Builds the compressed tree from a set of nodes
int build(vector<int> &v) // O( v.size() * maxlog )
{
    sort(all(v),cmp); // sort based on in-time
    
    vector<int> new_v = v; 
    
      // Add LCA of consecutive nodes to the new set
    for(int i = 1;i<v.size();i++)
    {
        new_v.pb( lca(v[i],v[i-1]) );
    }
    
    sort(all(new_v),cmp);
    new_v.resize(unique(all(new_v))-new_v.begin()); // Remove duplicates
    
    stack<int> st; 
    
    for(int k : new_v)
    {
          // Remove nodes from stack that are not ancestors of current node
        while(st.size() && out[k] > out[st.top()] ) st.pop();
        
        com_adj[k].clear(); // clean up
        
          // Add edge from parent into compressed tree
        if(st.size()) com_adj[st.top()].pb( mk(k, depth[k]-depth[st.top()] ) );
        st.push(k);
    }
    
    return new_v[0]; // Return root of compressed tree
}
//End Virtual Tree Code
 
int dp[maxn][2]; 
bool ch[maxn]; 

// solve problem
bool cal(int i)
{
    dp[i][0] = 1;  
    dp[i][1] = 0;  
    int mn = 0; 
    
    for(pii k : com_adj[i])
    {
        if(cal(k.fi))return 1; 
        if(ch[i])
        {
            if(ch[k.fi]&&k.se==1)return 1;
            
            dp[i][0] += dp[k.fi][0];
            dp[i][1] += dp[k.fi][0];
        }
        else 
        {
            dp[i][0] += min(dp[k.fi][0],dp[k.fi][1]);
            dp[i][1] += dp[k.fi][0];
            mn = min(mn,dp[k.fi][1] - dp[k.fi][0]);
        }
    }
  
    if(!ch[i])
    {
        dp[i][0] = min(dp[i][0],dp[i][1]);
        dp[i][1]+=mn; 
    }
    
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://codeforces.com/contest/613/problem/D
    
    int n;
    cin>>n;
    for(int i = 1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].pb(v); 
        adj[v].pb(u); 
    }
    dfs(1,0); 
    
    int q;
    cin>>q;
    while(q--)
    {
        int k;
        cin>>k;
        
        vector<int> v(k); 
        for(int i = 0;i<k;i++)
        {
            cin>>v[i]; 
            ch[v[i]] = 1; 
        }
        
        int s = build(v); // Build compressed tree
        
        
        if(cal(s))cout<<-1<<'\n'; 
        else cout<<min(dp[s][0],dp[s][1])<<'\n'; 
        
        for(int k : v)ch[k] = 0;
    }
    
    return 0;
}
