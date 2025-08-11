//Eulerian cycle
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

//Eulerian cycle code
bool deg[maxn];
bool used[maxn];
stack<int> st;

  // Finds Eulerian cycle using Hierholzer's algorithm, starting from node i.
void dfs(int i) // O( m )
{
  while(adj[i].size())
  {
    if(used[adj[i].back().se])
    {
      adj[i].pop_back(); // Skip used edge
      continue;
    }
    used[adj[i].back().se] = 1; // Mark edge as used
    dfs(adj[i].back().fi);      // Continue to next node
  }
  st.push(i); // Add node to Eulerian cycle
}
//End Eulerian cycle code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    //https://cses.fi/problemset/task/1691
    int n,m;
    cin>>n>>m;
    for(int i = 0;i<m;i++)
    {
      int u,v;
      cin>>u>>v;
      adj[u].pb(mk(v,i));
      adj[v].pb(mk(u,i));
      deg[u] ^= 1;  // Track node degree parity (odd/even)
      deg[v] ^= 1;
    }
    for(int i = 1;i<=n;i++)
    {
      if(deg[i])
      {
        cout<<"IMPOSSIBLE\n"; // Not Eulerian Cycle if any node has odd degree
        return 0;
      }
    }
    
    dfs(1); // Start Eulerian cycle from node 1
    if(st.size() != m+1)
    {
      cout<<"IMPOSSIBLE\n"; // Need to traverse every edge exactly once
      return 0;
    }
    
    // Output the Eulerian cycle
    for(;st.size();st.pop())cout<<st.top()<<' ';
    
    return 0;
}