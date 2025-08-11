//Euler tour
/* documents
https://wiki.vnoi.info/algo/graph-theory/euler-tour-on-tree.md
https://usaco.guide/gold/tree-euler?lang=cpp
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
vector<int> adj[maxn]; // Đồ Thị (Graph adjacency list)

//Euler tour code
int depth[maxn], in[maxn], out[maxn], t;

void dfs(int i, int pa) // O( n )
{
  depth[i] = depth[pa]+1;
  in[i] = ++t;            // entry time
  for(int k : adj[i])
  {
    if(k == pa) continue;
    dfs(k, i);            
  }
  out[i] = t;             // exit time
}
//End Euler tour code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}