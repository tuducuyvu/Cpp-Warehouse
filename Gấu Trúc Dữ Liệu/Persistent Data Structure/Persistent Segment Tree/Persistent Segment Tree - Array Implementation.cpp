// Persistent Segment tree - Array Imple
/* documents
  https://usaco.guide/adv/persistent?lang=cpp
  https://www.scaler.com/topics/data-structures/persistent-segment-tree
  https://www.youtube.com/watch?v=mLlaIj_8lv0
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

const int maxn = 2e5 + 10;
int a[maxn];

//Persistent Segment Tree Code

  // akvsdbvoaeib-  (!!!!)  it is recommended to use vector implementation to not risk out_of_bound

struct Node
{
    ll val;                // Value stored in this node (sum of segment)
    int l,r;            // Left and right children
} nodes[maxn * 22]; // (!) this array is shared for all per_segtree, remember to adjust the size 

int node_cnt; // count of all created nodes across all per_segtree that you are using 

struct per_segtree
{
    vector<int> root; // the root of all versions
    
    int treeL,treeR; // tree boundaries
    
    per_segtree() : treeL(0),treeR(0) {} // Initialize all members
    
    per_segtree(int l,int r) : treeL(l),treeR(r)
    {
          // Build initial version of the segment tree [l, r]
        root.reserve(maxn);
        root.pb(0); // fill root[0] 
        root.pb(build(l,r)); // root[1] 
    }
    
    int new_node(ll tmp,int L,int R)
    {
        ++node_cnt;
        nodes[node_cnt].val = tmp;
        nodes[node_cnt].l = L;
        nodes[node_cnt].r = R;
        return node_cnt;
    }
    
    int build(int tl,int tr) // O( n * log(n) )
    {
          // Recursively build the segment tree for range [tl, tr]
        if(tl == tr) return new_node(a[tl],0,0); // If leaf, create node with array value
        else
        {
            int mid = (tl + tr)/2;
            int L = build(tl,mid);           // Build left child
            int R = build(mid+1,tr);         // Build right child
            return new_node(nodes[L].val + nodes[R].val, L, R); 
        }
    }
    
    int update_recur(int id,int tl,int tr,int pos,int val) // O( log(n) )
    {
          // Recursively update position 'pos' to 'val' in version rooted at 'id'
        if(tl > tr || tl > pos || tr < pos)return id; // If out of range, return current node
        if(tl == tr) return new_node(val,0,0);            // If leaf, create new node with updated value
        
        int mid = (tl + tr)/2;
        
        int L = update_recur(nodes[id].l,tl,mid,pos,val);     // Update left child if needed
        int R = update_recur(nodes[id].r,mid+1,tr,pos,val);   // Update right child if needed
        
        return new_node(nodes[L].val + nodes[R].val,L,R);           // Create new node combining updated children
    }
    
    void update_ver(int ver,int pos,int val) 
    {
          // Update version 'ver' at position 'pos' with value 'val'
          // Produces a new root for version 'ver'
        root[ver] = update_recur(root[ver],treeL,treeR,pos,val);
    }
    
    ll cal_recur(int id,int l,int r,int tl,int tr) // O( log(n) )
    {
          // Recursively query sum in range [l, r] for subtree [tl, tr]
        if(l > r || tl > tr || tl > r || tr < l)return 0;   // No overlap
        if(tl >= l && tr <= r)return nodes[id].val;               // Complete overlap, return sum
        int mid = (tl + tr)/2;
          // Partial overlap, sum left and right children
        return cal_recur(nodes[id].l,l,r,tl,mid) + cal_recur(nodes[id].r,l,r,mid+1,tr);
    }
    
    ll cal_ver(int ver,int l,int r) 
    {
          // Query sum in range [l, r] for version 'ver'
        return cal_recur(root[ver],l,r,treeL,treeR);
    }
    
    void copy_ver(int ver) // O( 1 )
    {
          // Create a new version by copying root of version 'ver'
        root.pb(root[ver]);
    }
};
//End Persistent Segment Tree Code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    // https://cses.fi/problemset/task/1737
    
    int n,m;
    cin>>n>>m;
    
    for(int i = 1;i<=n;i++)
    {
        cin>>a[i];
    }
    
    per_segtree tree(1,n); // Initialize persistent segment tree for [1, n]
    
    while(m--)
    {
        int ch;
        cin>>ch;
        if(ch == 1)
        {
            int k,pos,val;
            cin>>k>>pos>>val;
            tree.update_ver(k,pos,val); // Update version k: set a[pos]=val
        }
        if(ch == 2)
        {
            int k,l,r;
            cin>>k>>l>>r;
            cout<<tree.cal_ver(k,l,r)<<'\n'; // Query sum in range [l, r] of version k
        }
        if(ch == 3)
        {
            int k;
            cin>>k;
            tree.copy_ver(k); // Create new version by copying version k
        }
    }
    
    return 0;
}