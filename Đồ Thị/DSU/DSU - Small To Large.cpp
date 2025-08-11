//DSU Small to Large
/* documents
https://usaco.guide/plat/merging?lang=cpp
https://youkn0wwho.academy/topic-list/dsu_on_tree
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

//DSU Small to Large code
int p[maxn];// parent[]
vector<int> a[maxn]; // data

  // Initializes DSU structures. Each node is its own parent and set.
void prepare() // O( n )
{
  for(int i = 1; i < maxn; i++)
  {
    p[i] = i;
    a[i] = {i}; // Each set contains only itself initially
  }
}

  // Finds the root of node 'i' with path compression
int fi(int i)// find root
{
  while(i != p[i]) i = p[i] = p[p[i]]; // Path Compression -> O( 1 ) overall
  return i;
}

  // Unites the sets containing 'u' and 'v'. Returns true if merged
bool unite(int u, int v) // O( n * log(n) ) overall
{
  u = fi(u), v = fi(v);
  if(u == v) return 0;
  if(a[u].size() < a[v].size()) swap(a[u],a[v]); // union by size
  p[v] = u;
  for(int k : a[v]) a[u].pb(k); // Merge the data from v into u
  return 1;
}
//End DSU Small to Large code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    return 0;
}