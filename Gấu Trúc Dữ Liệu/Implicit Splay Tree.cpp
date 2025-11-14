// Implicit Splay Tree
/*
  https://usaco.guide/adv/link-cut-tree#splay-tree
  https://ocw.mit.edu/courses/6-854j-advanced-algorithms-fall-2008/resources/lec6/
  https://web.stanford.edu/class/archive/cs/cs166/cs166.1146/lectures/08/Slides08.pdf
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

const int maxn =2e5 + 10;
int a[maxn];

// Implicit Splay Tree Code
struct splay_tree
{
    struct Node 
    {
        int cnt,sz;
        ll val,sum;
        Node *parent,*child[2];
        bool flip; // lazy flag
        Node(ll _val)
        {
            cnt = sz = 1;
            val = sum = _val;
            parent = child[0] = child[1] = nullptr;
            flip = 0;
        }
        
        bool direction(Node *x) { return child[1] == x;}
    } *root = nullptr;
    
    int get_sz(Node *x){ return (x?x->sz:0); }
    
    ll get_sum(Node *x){ return (x?x->sum:0); }
    
      // Updates current node
    void pull(Node *x)
    {
        if(x)
        {
            x->sz = x->cnt + get_sz(x->child[0]) + get_sz(x->child[1]);
            x->sum = x->val + get_sum(x->child[0]) + get_sum(x->child[1]);
        }
    }
    
      // Propagates 
    void push(Node *x)
    {
        if(x&&x->flip)
        {
            if(x->child[0])x->child[0]->flip^=1; 
            if(x->child[1])x->child[1]->flip^=1; 
            swap(x->child[0],x->child[1]); // Swap children to perform the reverse
            x->flip = 0; 
        }
    }
    
      // Recursively build a balanced splay tree from an array
    Node* build_recur(int l,int r)
    {
        if(l>r)return nullptr;
        int mid = (l+r)/2;
        Node *x = new Node(a[mid]); 
        
        x->child[0] = build_recur(l,mid-1);
        x->child[1] = build_recur(mid+1,r); 
        
        if(x->child[0])x->child[0]->parent = x; // adoption
        if(x->child[1])x->child[1]->parent = x; 
        
        pull(x); 
        return x;
    }
    
    void build(int l,int r)  { root = build_recur(l,r);}
      
      // Rotates node x up
    void rotate(Node *x)
    {
        Node *p = x->parent;
        Node *gp = p->parent;
        x->parent = gp; // x's new parent is p's parent
        if(gp)gp->child[gp->direction(p)] = x; // adoption
        else root = x; // If p was root, x becomes the new root
        
        bool c = p->direction(x); 
        p->child[c] = x->child[c^1]; // Move x's opposite child to p
        x->child[c^1] = p; 
        p->parent = x; // adoption
        if(p->child[c])p->child[c]->parent = p; 
        
        pull(p); // (!) update p first
        pull(x); 
    }
    
      // Splay :brings node x to the root of the tree
    void splay(Node *x)
    {
        if(!x)return;
        while(x->parent) 
        {
            Node *p = x->parent;
            if(p->parent) 
            {
                  // Determine if it's a zig-zig (same directionection) or zig-zag (different directionections) case
                if(p->parent->direction(p) == p->direction(x)) rotate(p); // Zig-zig: rotate p, then rotate x
                else rotate(x); // Zig-zag: rotate x, then rotate x again
            }
            rotate(x); // Zig: rotate x
        }
    }
    
      // Finds the rightmost node in the subtree rooted at x
    Node* find_end(Node *x)
    {
        if(!x)return nullptr;
        push(x); 
        while(x->child[1])
        {
            x=x->child[1];
            push(x);
        }
        return x;
    }
    
      // Finds the k-th element (1-indexed) in the subtree rooted at x
    Node* find_kth(Node *x,int k)
    {
        if(!x || k<=0 || k>get_sz(x))return nullptr; // invalid
        while(x)
        {
            push(x); 
            int tmp = get_sz(x->child[0])+x->cnt; 
            if(tmp==k)return x; // found
            if(tmp > k) x=x->child[0];
            else 
            {
                k-=tmp; 
                x=x->child[1];
            }
        }
        return nullptr;
    }
    
      // Detaches the right part of the tree , keeping the first k elements
    Node* detach_end(int k)
    {
        if(!root)return nullptr;
        Node *x = nullptr;
        if(k<=0||k>get_sz(root)) // invalid
        {
            if(k<=0)swap(root,x); // If k is 0 or less, detach the whole tree
            pull(root);
            return x;
        }
        x = find_kth(root,k); 
        splay(x); // Splay the k-th node to the root
        Node *ans = x->child[1]; 
        if(ans)
        {
            ans->parent = nullptr; 
            x->child[1] = nullptr; // disown
        }
        pull(x); 
        return ans;
    }
    
      // Merges a tree R to the right end of the current tree (root)
    void merge_end(Node *R)
    {
        if(!R)return; 
        if(!root) 
        {
            root = R;
            return;
        }
        
        Node *x = find_end(root); // Find the rightmost node in the current tree
        splay(x); // Splay it to the root
        x->child[1] = R; 
        if(R)R->parent = x; //adoption
        pull(x); 
    }
    
      // Reverses range [l,r]
    void reverse(int l,int r)
    {
        if(l>r)return; // Invalid
        
        Node *R = detach_end(r); // Detach the segment [r+1,end]
        Node *L = detach_end(l-1); // Detach the segment [l,r]
        if(L)L->flip^=1; 
        merge_end(L); // Re-merge the segment [l,r] (now reversed)
        merge_end(R); // Re-merge the right segment
    }
    
      // Calculates the sum of elements in the segment [l,r]
    ll cal(int l,int r)
    {
        if(l>r)return 0; // Invalid
        
        Node *R = detach_end(r); // Detach the segment [r+1,end]
        Node *L = detach_end(l-1); // Detach the segment [l,r]
        
        ll ans = get_sum(L);
        
        merge_end(L); // Re-merge the segment [l,r] (now reversed)
        merge_end(R); // Re-merge the right segment
        
        return ans;
    }
};
// Implicit Splay Tree Code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://judge.yosupo.jp/problem/range_reverse_range_sum
    
    int n,m;
    cin>>n>>m;
    
      // Read initial array elements
    for(int i = 1;i<=n;i++)
    {
        cin>>a[i]; 
    }
    
    splay_tree tree;
    
    tree.build(1,n);
    
    while(m--)
    {
        int ty,l,r;
        cin>>ty>>l>>r;
        l++; // lil adjust
        if(ty==0) 
        {
            tree.reverse(l,r); 
        }
        else 
        {
            cout<<tree.cal(l,r)<<'\n';
        }
    }
    
    return 0;
}
