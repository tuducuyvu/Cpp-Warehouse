// 2-Edge Connected Component
/* documents
  https://usaco.guide/adv/BCC-2CC
  https://codeforces.com/blog/entry/83980
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
vector<pii> adj[maxn]; // Graph
char ans[maxn];

//Code 2-Edge Connected Component
stack<int> st;
int com[maxn],low[maxn],tim[maxn];
int t,com_cnt;
vector<pii> com_adj[maxn]; // Compressed graph ( Bridge Tree )

  // DFS to find 2-edge connected component for each node
void dfs(int i,int pa) // O( n )
{
  low[i] = tim[i] = ++t; // Set discovery and low time
  st.push(i); // Add node to the stack
  bool through = 0;
  for(pii k : adj[i])
  {
      // Skip edge to parent (once (!) )
    if(k.fi == pa && !through)
    {
      through = 1;
      continue;
    }
    
    if(tim[k.fi])low[i] = min(low[i],tim[k.fi]);
    else 
    {
      dfs(k.fi,i);
      low[i] = min(low[i],low[k.fi]);
    }
  }
    // If node is root of a component
  if(low[i] == tim[i])
  {
    ++com_cnt;
      // Pop nodes from stack to form component
    while(st.top() != i)
    {
      com[st.top()] = com_cnt;
      st.pop();
    }
    com[st.top()] = com_cnt;
    st.pop();
  }
}

  // Build the compressed component graph ( Bridge Tree )
void compress_graph(int n) // O( n )
{
  for(int i = 1;i<=n;i++)
  {
    for(pii k : adj[i])
    {
        // Add edge between different components
      if(com[i] != com[k.fi]) com_adj[com[i]].pb( mk(com[k.fi],k.se) );
    }
  }
}
//End Code 2-Edge Connected Component

bool c[maxn];
int dp[maxn];

void cal(int i,int pa)
{
  c[i] = 1; 
  for(pii k : com_adj[i])
  {
    if(k.fi == pa)continue; 
    cal(k.fi,i); 
    dp[i] += dp[k.fi]; 
    dp[k.fi] *= k.se / abs(k.se); // change sign of edge
    
    if(dp[k.fi] < 0)ans[abs(k.se)] = 'R';
    if(dp[k.fi] > 0)ans[abs(k.se)] = 'L';
  }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://oj.uz/problem/view/CEOI17_oneway
    
    int n,m;
    cin>>n>>m;
    for(int i = 1;i<=m;i++)
    {
      int u,v;
      cin>>u>>v;
      adj[u].pb(mk(v,i));
      adj[v].pb(mk(u,-i)); // edges made of pairs are for solving the problem, dont mind it
      
      ans[i] = 'B'; 
    }
    
      // Find all 2-edge connected components
    for(int i = 1;i<=n;i++)
    {
      if(!tim[i]) dfs(i,0);
    }
    
      // Compress the graph using components
    compress_graph(n);
    
    int q;
    cin>>q;
    
    while(q--)
    {
      int u,v;
      cin>>u>>v;
      u = com[u];
      v = com[v];
      dp[u]++;
      dp[v]--;
    }
    
    for(int i = 1;i<=com_cnt;i++)
    {
      if(!c[i])cal(i,0);
    }
    
    for(int i = 1;i<=m;i++)cout<<ans[i];
    
    return 0;
}