// Splay Ordered_set
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

// Splay Ordered_set Code
struct splay_tree
{
    struct Node
    {
        int val, sz, cnt;
        Node *parent, *child[2];  // child[0] is left, child[1] is right

        Node()
        {
            val = 0;
            sz = cnt = 1; 
            parent = child[0] = child[1] = nullptr; 
        }

        bool direction(int tmp)
        {
            return tmp > val;
        }
    } *root = nullptr;

      // Return subtree size
    int sz(Node *x)
    {
        return (x ? x->sz : 0);
    }

      // Update current node
    void pull(Node *x)
    {
        if(x) x->sz = x->cnt + sz(x->child[0]) + sz(x->child[1]);
    }

      // Rotate x up
    void rotate(Node *x)
    {
        Node *p = x->parent;
        bool c = (x == p->child[1]);

        x->parent = p->parent; // p's parent is now x's parent 
        if(x->parent == nullptr) root = x; // if p was root, x becomes the new root
        else if(x->parent->child[0] == p) x->parent->child[0] = x; // adoption :)
        else x->parent->child[1] = x;

        p->child[c] = x->child[c ^ 1]; // move x's child to p's
        if(p->child[c]) p->child[c]->parent = p; // adoption

        x->child[c ^ 1] = p; // Make p a child of x
        p->parent = x; // adoption

        pull(p); // (!)Update size of p first
        pull(x); // Then update size of x
    }

      // Splay x to the root
    void splay(Node *x)
    {
        while(x->parent) // Continue until x is the root
        {
            Node *p = x->parent;
            if(p->parent) // grandpapa exists
            {
                  // Determine if it's a zig-zag (different directions) or zig-zig (same directions) case
                if(p->parent->direction(p->val) != p->direction(x->val)) rotate(x); // Zig-zag: rotate x, then rotate x again
                else rotate(p); // Zig-zig: rotate p, then rotate x
            }
            rotate(x); // Zig: rotate x
        }
    }

      // Find min node in the subtree rooted at x
    Node* find_min(Node *x)
    {
        while(x && x->child[0]) x = x->child[0];
        return x;
    }

      // Find max node in the subtree rooted at x
    Node* find_max(Node *x)
    {
        while(x && x->child[1]) x = x->child[1]; 
        return x;
    }

      // Find val or last accessed node
    Node* find(Node *x,int val)
    {
        Node *p = x; // Keep track of the last non-null node visited
        while(x)
        {
            p = x;
            if(val == x->val) break; // Value found
            if(val < x->val) x = x->child[0]; 
            else x = x->child[1]; 
        }
        return p; // Return the node where the search ended or the value was found
    }

      // Find predecessor (greater=0) or successor (greater=1) of val
    Node* find_near(int val,bool greater)
    {
        Node *x = root, *ans = nullptr, *p = x;

        while(x)
        {
            p = x; 
            if(val == x->val)
            {
                ans = x; // If value found, this is a potential answer
                break;
            }
            if(val < x->val)
            {
                if(greater) ans = x; // If looking for successor
                x = x->child[0];
            }
            else
            {
                if(!greater) ans = x; // If looking for predecessor
                x = x->child[1];
            }
        }

        if(p) splay(p); // Splay yourself NOW
        return ans;
    }

      // Split tree around x
    void split(Node *x,Node *&L,Node *&R)
    {
        splay(x); // Splay x to the root
        R = x->child[1];

        if(x->child[1])
        {
            R->parent = nullptr; // Disconnect R from x
            x->child[1] = nullptr; // disown
        }

        L = x; 
        pull(L); 
        pull(R); 
    }

      // merge tree L and R
    Node* join(Node *L,Node *R)
    {
        if(!L) return R; // if L is empty, R is the result
        if(!R) return L; // vice versa

        Node *x = find_max(L); // find the maximum element in L
        splay(x); // bring to root
        x->child[1] = R; 
        R->parent = x; // adoption
        pull(x);
        return x;
    }

      // Insert element
    void insert(int val)
    {
        Node *x = find(root,val); // find the potential insertion point or existing node

        if(!x) // if the tree is empty
        {
            root = new Node();
            root->val = val;
            return;
        }

        if(x->val == val)
        {
            // x->cnt++; for multiset?
        }
        else
        {
            bool c = x->direction(val); 
            x->child[c] = new Node(); 
            x->child[c]->parent = x; // adoption
            
            x = x->child[c]; 
            x->val = val; // Set the value
        }

        splay(x); // Splay yourself NOW
    }

      // Delete element
    void erase(int val)
    {
        Node *x = find(root,val); 
        if(x) splay(x);
        if(!x || x->val != val) return;

        Node *L,*R;
        split(x,L,R);
        L = L->child[0];
        if(L) L->parent = nullptr; 
        x->child[0] = nullptr; 
        delete(x); 

        root = join(L,R);
    }

      // rank of val ( number of element <= val)
    int get_rank(int val)
    {
        Node *x = root;
        int ans = 0;
        Node *p = x;

        while(x)
        {
            p = x;
            if(x->val <= val)
            {
                ans += sz(x->child[0]) + x->cnt; 
            }
            if(val == x->val) break; 
            if(val < x->val) x = x->child[0]; 
            else x = x->child[1]; 
        }

        if(p) splay(p); // Splay yourself NOW
        return ans;
    }

      // 1-based k-th element
    Node* get_kth(int k)
    {
        Node *x = root;
        if(k <= 0 || k > sz(x)) return nullptr; // invalid

        while(x)
        {
            if(k > sz(x->child[0]) + x->cnt)
            {
                k -= sz(x->child[0]) + x->cnt; 
                x = x->child[1];
            }
            else if(k <= sz(x->child[0])) 
            {
                x = x->child[0]; 
            }
            else 
            {
                break; // Found
            }
        }

        if(x) splay(x); // Splay yourself NOW
        return x;
    }
};
// End  Splay Ordered_set Code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://judge.yosupo.jp/problem/ordered_set

    splay_tree s;

    int n,q;
    cin >> n >> q;

      // Insert initial elements into set
    while(n--)
    {
        int tmp;
        cin >> tmp;
        s.insert(tmp);
    }

    while(q--)
    {
        int ty,x;
        cin >> ty >> x;

        if(ty == 0) s.insert(x); 
        else if(ty == 1) s.erase(x); 
        else if(ty == 2) 
        {
            auto it = s.get_kth(x);
            cout<<(it? it->val : -1)<<'\n';
        }
        else if(ty == 3) cout<<s.get_rank(x)<<'\n'; 
        else if(ty == 4)
        {
            auto it = s.find_near(x,0);
            cout<<(it? it->val : -1)<<'\n';
        }
        else if(ty == 5) 
        {
            auto it = s.find_near(x,1);
            cout<<(it? it->val : -1)<<'\n';
        }
    }

    return 0;
}
