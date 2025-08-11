// topo
/* documents
https://wiki.vnoi.info/algo/graph-theory/topological-sort.md
https://usaco.guide/gold/toposort?lang=cpp
https://cp-algorithms.com/graph/topological-sort.html
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
const int maxn = 1e6 + 10;
vector<int> adj[maxn];// Đồ Thị (Graph adjacency list)

// topo code
int c[maxn];
stack<int> st;

  // Returns true if a cycle is detected
bool topo(int i) // O( n )
{
  c[i] = 1; // Mark node as visiting
  for(int k : adj[i])
  {
    if(c[k] == 1)return 1; // true -> cycle (invalid)
    if(c[k] == 2)continue; // Skip if node already processed
    if(topo(k))return 1;   // Recurse for adjacent nodes
  }
  c[i] = 2; // Mark node as fully processed
  st.push(i); // Add node to topological order
  return 0;
}
//End topo code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    //https://cses.fi/problemset/task/1679
    int n,m;
    cin>>n>>m;
    while(m--)
    {
      int u,v;
      cin>>u>>v;
      adj[u].pb(v);
    }
    
    for(int i = 1;i<=n;i++)
    {
      if(c[i] == 0 && topo(i)) // cycle detected
      {
        cout<<"IMPOSSIBLE";
        return 0;
      }
    }
    
    // Print nodes in topological order
    for(;st.size();st.pop())cout<<st.top()<<' ';
    
    return 0;
}