//Eulerian path
/* documents
https://wiki.vnoi.info/vi/algo/graph-theory/euler-cycle
https://cp-algorithms.com/graph/euler_path.html
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
vector<pii> adj[maxn];// Đồ Thị (Graph adjacency list)

//Eulerian path code
int deg[maxn];
bool used[maxn];
stack<int> st;

  // Hierholzer's algorithm for Eulerian path; builds the path in st.
void dfs(int i) // O( m )
{
  while(adj[i].size())
  {
    if(used[adj[i].back().se])
    {
      adj[i].pop_back(); // Skip if edge already used
      continue;
    }
    used[adj[i].back().se] = 1; // Mark edge as used
    dfs(adj[i].back().fi);      // Visit next node recursively
  }
  st.push(i); // Add node to path on backtracking
}
//End Eulerian path code


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    //https://cses.fi/problemset/task/1693
    int n,m;
    cin>>n>>m;
    for(int i = 0;i<m;i++)
    {
      int u,v;
      cin>>u>>v;
      adj[u].pb(mk(v,i));
      deg[u]++;       // Out-degree for node u
      deg[v]--;       // In-degree for node v (tracked as negative)
    }
    // Check for valid Eulerian path from 1 to n
    if(deg[1] != 1 && deg[n] != -1)
    {
      cout<<"IMPOSSIBLE\n";
      return 0;
    }
    for(int i = 2;i<n;i++)
    {
      if(deg[i])
      {
        cout<<"IMPOSSIBLE\n"; // All intermediate nodes must be balanced
        return 0;
      }
    }
    
    dfs(1); // Build Eulerian path starting from node 1
    if(st.size() != m+1)
    {
      cout<<"IMPOSSIBLE\n"; // Not all edges were used
      return 0;
    }
    
    for(;st.size();st.pop())cout<<st.top()<<' '; // Output the path
    
    return 0;
}