//Dijkstra
/* documents
https://wiki.vnoi.info/algo/graph-theory/shortest-path
https://cp-algorithms.com/graph/dijkstra.html
https://usaco.guide/gold/shortest-paths?lang=cpp
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
typedef pair<ll,int> pii;

const int maxn = 2e5 + 10;
vector<pii> adj[maxn]; // Đồ Thị (Graph adjacency list)

//Dijkstra code
priority_queue<pii,vector<pii>,greater<pii>>q;
ll dis[maxn];

  // Computes shortest paths from node s to all other nodes.
void Dijkstra(int s) // O( (n + m) * log(n) )
{
  for(int i = 1;i<maxn;i++)dis[i] = LLONG_MAX; // Initialize distances to infinity
  dis[s] = 0;
  q.push(mk(0,s)); // Start from source node
  while(q.size())
  {
    ll w = q.top().fi;
    int i = q.top().se;
    q.pop();
    if(w != dis[i])continue; // Skip if this is an outdated entry

    for(pii k : adj[i])
    {
      if(dis[k.fi] > w + k.se)
      {
        dis[k.fi] = w + k.se; // Update distance if a shorter path is found
        q.push(mk(dis[k.fi],k.fi)); // Push the updated node into the queue
      }
    }
  }
}
//End Dijkstra code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}