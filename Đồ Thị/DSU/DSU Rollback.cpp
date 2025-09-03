// DSU rollback
/* documents
    https://wiki.vnoi.info/algo/data-structures/dsu-rollback
    https://usaco.guide/adv/offline-del?lang=cpp
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

int ans[maxn];

//Code DSU Rollback
struct DSUrollback
{
    vector<pii> t[maxn * 4]; // the timeline, represented with a segment tree for updates
    
    int p[maxn],s[maxn]; // DSU parent/size []
    int cnt,total_range;
    
    DSUrollback(int n,int q)
    {
        cnt = n; // Initially n components
        total_range = q; // we query on the [0,q] timeline range 
        
          // Initialise DSU 
        for(int i = 1;i<=n;i++)
        {
            p[i] = i;
            s[i] = 1;
        }
    }
    
      // Add edge to timeline , range [l, r]
    void up(int i,int l,int r,int tl,int tr,pii edge) // O( log(total_range) )
    {
        if(l > r || tl > tr || tl > r || tr < l)return;
        
          // If current timeline segment is fully within [l, r], add the edge
        if(tl >= l && tr <= r)
        {
            t[i].pb(edge);
            return;
        }
        
        int mid = (tl + tr)/2,ii = i * 2;
        up(ii,l,r,tl,mid,edge);
        up(ii+1,l,r,mid+1,tr,edge);
    }
    
    stack<pii> st;
    
      // Find root of component ( WITHOUT path compression ! )
    int fi(int i) // O( log(n) )
    {
        while(i != p[i])i = p[i];
        return i;
    }
    
      // Join two components, update DSU and history stack
    bool unite(int u,int v) // O( log(n) )
    {
        u = fi(u);
        v = fi(v);
        if(u == v)return 0;
          // Union by size
        if(s[u] < s[v])swap(u,v);
        
        p[v] = u;
        s[u] += s[v];
        
        st.push(mk(u,v)); // Store this merge for rollback
        cnt--;
        
        return 1;
    }
    
      // Undo lastest union operation (for segment tree traversal)
    void rollback() // O( 1 )
    {
        pii edge = st.top();
        st.pop();
        p[edge.se] = edge.se; // Restore parent
        s[edge.fi] -= s[edge.se]; // Restore size
        cnt++;
    }
    
    
      // DFS traversal of segment tree, applying and rolling back merges
    void walk(int i,int tl,int tr) // O( total_range * log(total_range) * log(n) )
    {
        if(tl > tr)return;
    
        int pend = 0; // number of pending rollback of this node
        
          // Apply all edges in current segment
        for(pii k : t[i]) pend += unite(k.fi,k.se);
        
          // If leaf, save answer and rollback
        if(tl==tr)
        {
            ans[tl] = cnt;
            while(pend--)rollback();
            return;
        }
        
        int mid = (tl + tr)/2,ii = i*2;
        walk(ii,tl,mid);
        walk(ii+1,mid+1,tr);
        
          // Rollback all merges done in this segment
        while(pend--)rollback();
    }
    
      // Ensure edges is unique
    void reformat(pii & edge) // O( 1 )
    {
        if(edge.fi > edge.se)swap(edge.fi,edge.se);
    }
    
    map<pii,int>mp; // Map for edge activation time
    
      // check if this edge is active
    bool exist(pii edge) // O( log(m) )
    {
        map<pii,int>::iterator it = mp.find(edge);
        return (it != mp.end() && it->se != -1);
    }
    
      // Add edge at start_time
    void add_edge(pii edge,int start_time) // O( log(m) )
    {
        reformat(edge);
        if(!exist(edge)) mp[edge] = start_time;
    }
    
      // Remove: schedule edge to be active from mp[edge] to i-1
    void remove_edge(pii edge,int end_time) // O( log(m) + log(total_range) )
    {
        reformat(edge);
        if(exist(edge))
        {
            up(1,mp[edge],end_time,0,total_range,edge);
            mp[edge] = -1; // deactivate this edge
        }
    }
    
      // For all edges still active, schedule them to be active till end
    void flush() // O( m * log(m) )
    {
        for(pair<pii,int> k : mp) 
            if(k.se>=0) up(1,k.se,total_range,0,total_range,k.fi);
    }
};
//End Code DSU Rollback 

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/2133

    int n,m,q;
    cin>>n>>m>>q;
    
    DSUrollback DSU(n,q);

      // Read initial edges, mark as active from time 0
    while(m--)
    {
        pii edge;
        cin>>edge.fi>>edge.se;
        
        DSU.add_edge(edge,0);
    }

      // Process queries: add or remove edges
    for(int i = 1;i<=q;i++)
    {
        pii edge;
        int ch;
        cin>>ch>>edge.fi>>edge.se;
        
        if(ch==1) DSU.add_edge(edge,i);
        else DSU.remove_edge(edge,i-1);
    }
    
    DSU.flush();
    
      // Traverse segment tree to compute answers
    DSU.walk(1,0,q);

      // Output the answer for each time point
    for(int i = 0;i<=q;i++)cout<<ans[i]<<' ';
    
    return 0;
}