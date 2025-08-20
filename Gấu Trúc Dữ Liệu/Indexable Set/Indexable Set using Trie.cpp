// Trie-ordered_set
/*

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

// Trie-ordered_set Code
template <int maxlog,int offset> struct Trie
{
    struct Node 
    {
        int child[2];
        int cnt;
    }nodes[maxn * maxlog];
    
    int N;
    int sz;
    
      // Initializes the Trie to an empty state
    void reset()
    {
        N = 0;
        sz = 0;
        memset(nodes[0].child,-1,sizeof(nodes[0].child)); // root node children
        nodes[0].cnt = 0;
    }
    
    Trie()
    {
        reset(); // Constructor sets up an empty Trie
    }
    
      // Returns current size of the Trie
    int size()
    {
        return sz;
    }
    
      // Checks if Trie is empty
    bool empty()
    {
        return sz == 0;
    }
    
      // Allocates a new node in the Trie
    int new_node()
    {
        N++;
        memset(nodes[N].child,-1,sizeof(nodes[N].child));
        nodes[N].cnt = 0;
        return N;
    }
    
      // Checks if a value is present in the Trie
    bool find(int val)
    {
        int pos = 0;
        for(int i = maxlog;i>=0;i--)
        {
            bool c = (val>>i) & 1; // Get bit at position i
            if(nodes[pos].child[c] == -1) return 0; // If child doesn't exist, value not found
            pos = nodes[pos].child[c];
        }
        return 1;
    }
    
      // Inserts a value if it's not already present
    void insert(int val)
    {
        val += offset; // offset for negative values
        if(find(val))return; // Prevent duplicates
        int pos = 0;
        for(int i = maxlog;i>=0;i--)
        {
            bool c = (val>>i) & 1;
            if(nodes[pos].child[c] == -1) nodes[pos].child[c] = new_node(); // Create node if not exists
            pos = nodes[pos].child[c];
            nodes[pos].cnt++; // Increase count for this path
        }
        sz++;
    }
    
      // Recursively erases a value from the Trie
    bool erase_recur(const int & val,int pos,int i)
    {
        if(i >= 0)
        {
            bool c = (val>>i) & 1;
            if(erase_recur(val,nodes[pos].child[c],i-1)) nodes[pos].child[c] = -1; // Remove child if empty
        }
        
        if(pos != 0)nodes[pos].cnt--; // Decrease count for this node
        return nodes[pos].cnt == 0; // Return if node is empty
    }
    
      // Removes a value if present
    void erase(int val)
    {
        val += offset;
        if(find(val))
        {
            erase_recur(val,0,maxlog); // Start recursive erase
            sz--;
        }
    }
  
      // Returns number of elements strictly less than val
    int order_of_key(int val)
    {
        val += offset;
        int pos = 0, ans = 0;
        for (int i = maxlog; i >= 0; i--)
        {
            bool c = (val >> i) & 1;
            if (c)
            {
                if (nodes[pos].child[0] != -1) ans += nodes[nodes[pos].child[0]].cnt; // Count left subtree
                if (nodes[pos].child[1] == -1) return ans; // No further path
                pos = nodes[pos].child[1];
            }
            else
            {
                if (nodes[pos].child[0] == -1) return ans; // No left child, return answer
                pos = nodes[pos].child[0];
            }
        }
        return ans;
    }

      // Finds the value at the given index (0-based), returns true if found
    bool find_by_order(int idx,int &ans)
    {
        if(idx >= sz || idx < 0)return 0; // Index out of bounds
        int pos = 0;
        ans = 0;
        for(int i = maxlog;i>=0;i--)
        {
            ans <<= 1; // Shift result to next bit
            if (nodes[pos].child[1] == -1) 
            {
                pos = nodes[pos].child[0];
            }
            else
            {
                if(nodes[pos].child[0] == -1)
                {
                    pos = nodes[pos].child[1];
                    ans |= 1;
                }
                else
                {
                    if(idx >= nodes[nodes[pos].child[0]].cnt)
                    {
                        idx -= nodes[nodes[pos].child[0]].cnt; // Move to right child
                        pos = nodes[pos].child[1];
                        ans |= 1;
                    }
                    else pos = nodes[pos].child[0]; // Move to left child
                }
            }
        }
        ans -= offset; // Reverse offset before returning
        return 1;
    }
};

//End Trie-ordered_set Code

Trie<31,1000000000> s; // Trie for 32-bit integers, offset for negatives

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://www.spoj.com/problems/ORDERSET
    
    
    int n;
    cin >> n;
    while(n--)
    {
        char ch;
        int i;
        cin >> ch >> i;
        if(ch == 'I')
        {
            s.insert(i); // Insert value i
        }
        else if(ch == 'D')
        {
            s.erase(i); // Delete value i
        }
        else if(ch == 'K')
        {
            int ans;
            if(s.find_by_order(i-1,ans))
            {
                cout << ans << '\n'; // Print value at position i
            }
            else cout << "invalid\n";
        }
        else
        {
            cout << s.order_of_key(i) << '\n'; // Print count of elements less than i
        }
    }
    
    return 0;
}
