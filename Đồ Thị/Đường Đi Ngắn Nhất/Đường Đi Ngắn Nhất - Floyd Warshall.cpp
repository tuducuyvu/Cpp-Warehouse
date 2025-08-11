//floydWarshall
/* documents
https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html
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

const int maxn = 5e2 + 10;
ll adj[maxn][maxn]; // Đồ Thị ( Adjacency Matrix )

//floydWarshall code
  // Computes shortest paths between all pairs of nodes.
void floydWarshall(int n) // O( n ^ 3 )
{
  for(int mid = 1;mid<= n;mid++)
  {
    for(int u = 1;u<=n;u++)
    {
      for(int v = 1;v<=n;v++)
      {
        // Try updating u->v path through node mid
        adj[u][v] = min(adj[u][v],adj[u][mid] + adj[mid][v]);
      }
    }
  }
}
//End floydWarshall code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}