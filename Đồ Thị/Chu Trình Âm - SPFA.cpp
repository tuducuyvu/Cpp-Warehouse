// Cycle SPFA
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

// Cycle SPFA code
int cnt[maxn],p[maxn];
ll dis[maxn];
bool in_queue[maxn];
deque<int> q;

  // SPFA variant to detect negative cycles.
  // Returns a node in the negative cycle if found, else 0.
int spfa(int s,int n) // O( n * m ) worst case
{
  dis[s] = 0;
  q.pb(s);              // Start from source
  in_queue[s] = 1;
  while(q.size())
  {
    int i = q.front();
    q.pop_front();
    in_queue[i] = 0;    // Mark node as processed (not in queue)
    for(pii k : adj[i])
    {
      if(dis[k.fi] > dis[i] + k.se)
      {
        dis[k.fi] = dis[i] + k.se; // Relax edge
        p[k.fi] = i;               // Track parent for path
        if(!in_queue[k.fi])
        {
          q.pb(k.fi);
          in_queue[k.fi] = 1;
          cnt[k.fi]++;
          if(cnt[k.fi] > n)
          {
            return k.fi; // Negative Cycle detected
          }
        }
      }
    }
  }
  return 0;
}
//End Cycle SPFA code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    //https://cses.fi/problemset/task/1197
    int n,m;
    cin>>n>>m;
    while(m--)
    {
      int u,v,w;
      cin>>u>>v>>w;
      adj[u].pb(mk(v,w));
    }
    for(int i = 1;i<=n;i++)dis[i] = LLONG_MAX;
    for(int i = 1;i<=n;i++)
    {
      if(dis[i] == LLONG_MAX)
      {
        int k = spfa(i,n); // Try to find negative cycle from i
        if(k) // found cycle
        {
          stack <int> st;
          map<int,bool> mp;
          
          // Build the negative cycle path
          while(!mp[k])
          {
            mp[k] = 1;
            st.push(k);
            k = p[k];
          }
          st.push(k); // Push the start of the cycle
          cout<<"YES\n";
          while(st.size())
          {
            cout<<st.top()<<' ';
            st.pop();
            if(st.top() == k)
            {
              cout<<k;
              break;
            }
          }
          return 0;
        }
      }
    }
    cout<<"NO";
    
    return 0;
}