//Hamiltonian Path
/* documents
https://en.wikipedia.org/wiki/Hamiltonian_path
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
 
const int maxn = 20;
vector<int> adj[maxn];// Đồ Thị (Graph adjacency list)
 
//Hamiltonian Path code
bool dp[1<<maxn][maxn];
bool in_queue[1<<maxn][maxn];
 
  // Returns true if there is a Hamiltonian path from u to v using BFS with DP.
  // n is the number of nodes; nodes are 0-indexed.
bool hamiltonian(int u,int v,int n) // path from u -> v , O( 2^n * n ^ 2 )
{
  deque<pii> q;
  q.pb(mk((1<<u),u));
  dp[1<<u][u] = 1;
  in_queue[1<<u][u] = 1;
  while(q.size())
  {
    int mask = q.front().fi;
    int i = q.front().se;
    q.pop_front();
    in_queue[mask][i] = 0;
    for(int k : adj[i])
    {
      if((mask>>k & 1) == 0) // Visit k if not yet visited in mask
      {
        int new_mask = mask | (1<<k); // Add k to the visited mask
        dp[new_mask][k] |= dp[mask][i];
        if(!in_queue[new_mask][k])
        {
          q.pb(mk(new_mask,k));
          in_queue[new_mask][k] = 1;
        }
      }
    }
  }
  return dp[(1<<n) - 1][v]; // True if all nodes visited and end at v
}
//End Hamiltonian Path code
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n,m;
    cin>>n>>m;
    while(m--)
    {
      int u,v;
      cin>>u>>v;
      u--;
      v--;
      adj[u].pb(v);
    }
    cout<<hamiltonian(0,n-1,n); // Check for Hamiltonian path from 0 to n-1
    
    return 0;
}