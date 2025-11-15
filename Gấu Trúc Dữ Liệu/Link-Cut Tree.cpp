// Link Cut Tree
/*
  https://usaco.guide/adv/link-cut-tree?lang=cpp
  https://courses.csail.mit.edu/6.851/spring21/scribe/lec19.pdf
  https://courses.csail.mit.edu/6.851/spring21/lectures/L19.htm
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

// Link-Cut Tree Code
struct Node
{
    int label,cnt,sz; 
    Node *parent, *child[2]; // child[0] for left, child[1] for right
    int lazy; // lazy flag for... whatever 
    Node()
    {
        cnt = sz = 1;
        lazy = 0;
        parent = child[0] = child[1] = nullptr;
    }
    
      // Determines if the node is a left (0) or right (1) child of its parent
      // Returns -2 if it has no parent (is a root of the represented tree), -1 if not a directionect child ( different splay trees / preferred paths)
    int direction()
    {
        if(!parent)return -2;
        if(parent->child[0] == this)return 0;
        if(parent->child[1] == this)return 1;
        return -1;
    }
    
      // Checks if the node is root of its current splay tree
    bool is_root()
    {
        return direction()<0;
    }
}nodes[maxn];

int get_sz(Node *x) { return (x?x->sz:0);}

void pull(Node *x)
{
    if(!x)return;
    x->sz = x->cnt + get_sz(x->child[0]) + get_sz(x->child[1]);
}

void push(Node *x)
{
    if(!x|| x->lazy== 0)return;
      // for example, here is reverse operation : 
    swap(x->child[0],x->child[1]);
    if(x->child[0])x->child[0]->lazy ^= 1;
    if(x->child[1])x->child[1]->lazy ^= 1;
    x->lazy = 0;
}

/*
  Each preferred path is represented by a Binary Search Tree (we use implicit splay here)
  Position of a node in the BST is the depth of that node (from the start of the preferred path)
*/

  // Performs a rotation to move node x up the splay tree
void rotate(Node *x)
{
    bool c = x->direction();
    Node *p = x->parent;
    
    x->parent = p->parent;
    if(!p->is_root()) p->parent->child[p->direction()] = x;
    
    p->child[c] = x->child[c^1]; 
    if(p->child[c])p->child[c]->parent = p; // adoption
    x->child[c^1] = p; 
    p->parent = x; 
    
    pull(p); // (!) update p first
    pull(x);
}

stack<Node*>st;
/* NOTE FOR REVERSAL OPERATIONS :
  Since we are traversing from the node to root, we need to push from root first down to node
  (to determine the shape of the tree, or else splay will fail)
*/
void push_to(Node *x)
{
    for(;!x->is_root();x=x->parent) st.push(x);
    st.push(x);
    for(;st.size();st.pop()) push(st.top());
}

  // bring x to root of the current splay tree
void splay(Node *x)
{
    if(!x)return;
    //push_to(x); ?
    while(!x->is_root()) 
    {
        Node *p = x->parent; 
        if(!p->is_root()) // (zig-zig or zig-zag case)
        {
            if(p->direction() == x->direction())rotate(p); 
            else rotate(x);
        }
        rotate(x);
    }
}

  // Makes node x the root of its represented tree and exposes the path from x to the actual root 
void access(Node *x)
{
    for(Node *cur = x, *pre = nullptr; cur; pre=cur, cur=cur->parent)
    {
        splay(cur); 
        cur->child[1] = pre; // Set its right child to the previously accessed node (form the path from root to x)
        pull(cur);
    }
    splay(x); // Finally, splay x to ensure it's the root of its splay tree
}

int lca(Node *u,Node *v)
{
    if(u==v)return u->label; 
    access(u); 
    access(v); 
    splay(u); 
    /*
      case 1: u is ancestor of v => preferred path of access(v) contains both u and v
      case 2: v is ancestor of u => after access(v), preferred path from root to u got cut off at v => path-parent of preferred path containing u is v
      case 3: u and v are in different subtrees => after access(v), preferred path from root to u got cut off at LCA 
    */
    return ( u->parent ? u->parent->label : u->label );
}

  // Links node x to node p, making p the parent of x
  // Assumes x and p are in different trees
void link(Node *x,Node *p)
{
    access(x);
    access(p); 
    x->parent = p; // (!) only set path-parent link
}

  // Cuts node x from its parent
  // Assumes x is not the root of its represented tree
void cut(Node *x)
{
    access(x); 
    if(x->child[0])
    {
        x->child[0]->parent = nullptr; // Disconnect the left child (which contains the ancestors in the preferred path)
        x->child[0] = nullptr; 
        pull(x); 
    }
}

  // Make x the root of the represented tree
void make_root(Node *x)
{
    if(!x)return;
    access(x);
    /* 
      after access(x), x is at the end of the preferred path , and when splayed, x only have left child ( ancestors )
      if we reverse this whole preferred path, all ancestors are converted into descendants, with same depth preserved
    */
    x->lazy ^= 1; 
    push(x);
}
//End Link-Cut tree Code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n,m; 
    cin>>n>>m;
    for(int i = 1;i<=n;i++)nodes[i].label = i;
    
    while(m--) 
    {
        string ty;
        cin>>ty;
        if(ty=="lca")
        {
            int u,v;
            cin>>u>>v;
            cout<<lca(&nodes[u],&nodes[v])<<'\n';
        }
        else if(ty=="link")
        {
            int u,v;
            cin>>u>>v;
            link(&nodes[u], &nodes[v]); 
        }
        else
        {
            int u;
            cin>>u;
            cut(&nodes[u]); 
        }
    }
    
    return 0;
}

// sorry i yapped too much
