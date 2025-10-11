// Centroid Decomposition
/* documents
  https://usaco.guide/plat/centroid?lang=cpp
  https://wiki.vnoi.info/vi/algo/graph-theory/centroid-decomposition
  https://oj.vnoi.info/post/72-noobcpp
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

const int maxn = 1e5 + 10;
vector<int> adj[maxn];

// Centroid Decomposition Code
int s[maxn];
bool used[maxn];

  // Calculates subtree sizes for each node in the tree
void cal(int i,int p)
{
    s[i] = 1;
    for(int k : adj[i])
    {
        if(k==p || used[k])continue;
        cal(k,i);
        s[i] += s[k];
    }
}

  // Finds the centroid of a subtree rooted at 'i' with total size 'sz'
int get(int i,int p,int sz)
{
    for(int k : adj[i])
    {
        if(k==p || used[k])continue;
        if(s[k]*2 > sz)return get(k,i,sz);
    }
    return i;
}

int depth[maxn];

  // Decomposes the tree into a centroid tree
void decompose(int root,int p)
{
    cal(root,0);
    int centroid = get(root,0,s[root]);
    used[centroid] = 1;
    
    depth[centroid] = depth[p]+1; // optional
    
    /*
      calculate here
      bla bla bla
    */
    
    for(int k : adj[centroid])
    {
        if(!used[k]) decompose(k,centroid);
    }
}
// End Centroid Decomposition

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://codeforces.com/contest/321/problem/C
    
    int n;
    cin>>n;
    for(int i = 1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    decompose(1,0);
    
    for(int i = 1;i<=n;i++)cout<<char('A'+depth[i] - 1)<<' ';
    
    return 0;
}
