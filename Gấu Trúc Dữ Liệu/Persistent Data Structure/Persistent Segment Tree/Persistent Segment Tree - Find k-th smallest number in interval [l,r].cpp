// Persistent segment tree for K-th number queries
/* documents
  https://cp-algorithms.com/data_structures/segment_tree.html?#finding-the-k-th-smallest-number-in-a-range
  https://usaco.guide/adv/persistent
  https://codeforces.com/blog/entry/89571
  https://codeforces.com/blog/entry/51609
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
int a[maxn];
vector<int> b;

// yeah basically this is a prefixsum for segment tree :)
struct per_segtree
{
    struct Node
    {
        int val;
        Node *l,*r;
        
        Node(){} // Default constructor
        Node(int tmp):val(tmp){} // Leaf node constructor
        Node(int tmp,Node *L,Node *R):val(tmp),l(L),r(R){} 
    };
    
    vector<Node*>root; // the root of all versions
    
    int treeL,treeR;  // tree boundaries
    
    per_segtree(){}
      // Initialize the segment tree from [l, r]
    per_segtree(int l,int r) : treeL(l),treeR(r)
    {
        root.reserve(maxn);
        root.pb(build(l,r)); // root[0] 
    }
    
      // Recursively build the segtree with all zeros
    Node *build(int tl,int tr) // O( n * log(n) )
    {
        if(tl == tr) return new Node(0); // Leaf node
        int mid = (tl + tr)/2;
        Node *L = build(tl,mid); // Build left child
        Node *R = build(mid+1,tr); // Build right child
        return new Node(0,L,R); 
    }
    
      // Create new version by updating position 'pos'
    Node *update_recur(Node *id,int tl,int tr,int pos) // O( log(n) )
    {
        if(tl > tr || tl > pos || tr < pos) return id; // Out of range, return current node
        if(tl == tr) return new Node(id->val + 1); // Leaf node, increment count
        int mid = (tl + tr)/2;
        Node *L = update_recur(id->l,tl,mid,pos); // Update left child
        Node *R = update_recur(id->r,mid+1,tr,pos); // Update right child
        return new Node(L->val + R->val,L,R); 
    }
    
      // Update tree to next version with added position
    void update_ver(int pos)
    {
        root.pb(update_recur(root.back(),treeL,treeR,pos)); // Store new tree version
    }
    
      // Walk through the tree to find the k-th smallest number
      // By finding the first position with prefixsum >= k 
    int walk(Node *lid, Node *rid,int tl,int tr,int sum,int k) // O( log(n) )
    {
        if(tl == tr) return tl; // Found the k-th smallest, return index
        int mid = (tl + tr)/2;
        int tmp = rid->l->val - lid->l->val; // Count in left child
        if(sum + tmp >= k) return walk(lid->l,rid->l,tl,mid,sum,k); 
        return walk(lid->r,rid->r,mid+1,tr,sum + tmp,k); 
    }
    
      //find index of k-th smallest in [l, r]
    int find(int l,int r,int k)
    {
        return walk(root[l-1],root[r],treeL,treeR,0,k); // Query between versions
    }
};
//End

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://www.spoj.com/problems/MKTHNUM
    
    int n,m;
    cin>>n>>m;
    b.reserve(n);
    for(int i = 1;i<=n;i++)
    {
        cin>>a[i];
        b.pb(a[i]);
    }
    
    sort(all(b));
    b.resize(unique(all(b)) - b.begin()); // compress
    
    per_segtree tree(1,b.size()); // Build persistent segment tree
    
    for(int i = 1;i<=n;i++)
    {
        a[i] = upper_bound(all(b),a[i]) - b.begin(); // compress
        tree.update_ver(a[i]); // Build version for each prefix
    }
    
    while(m--)
    {
        int l,r,k;
        cin>>l>>r>>k;
        cout<<b[tree.find(l,r,k)-1]<<'\n'; 
    }
    
    
    return 0;
}