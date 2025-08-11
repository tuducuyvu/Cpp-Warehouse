// SPFA
/* documents
https://wiki.vnoi.info/algo/graph-theory/shortest-path-2
https://wiki.vnoi.info/algo/graph-theory/spfa
https://cp-algorithms.com/graph/bellman_ford.html
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

const int maxn = 25e2 + 10;
vector<pii> adj[maxn]; // Đồ Thị (Graph adjacency list)

// SPFA code
int cnt[maxn];
ll dis[maxn];
bool in_queue[maxn];
deque<int> q;

  // Computes the shortest paths from s to all nodes using SPFA algorithm.
  // Detects negative cycles if any node is relaxed more than n times.
void spfa(int s,int n) // O( n * m ) worst case
{
  dis[s] = 0;
  q.pb(s);               // Start from source node
  in_queue[s] = 1;
  while(q.size())
  {
    int i = q.front();
    q.pop_front();
    in_queue[i] = 0;     // Mark node as not in queue
    for(pii k : adj[i])
    {
      if(dis[k.fi] > dis[i] + k.se)
      {
        dis[k.fi] = dis[i] + k.se;   // Update distance if a shorter path is found
        if(!in_queue[k.fi])
        {
          q.pb(k.fi);                // Add node to queue for further processing
          in_queue[k.fi] = 1;
          cnt[k.fi]++;
          if(cnt[k.fi] > n)
          {
            return; // Negative Cycle
          }
        }
      }
    }
  }
}
//End SPFA code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}