// Walk on Segment Tree 2N - Find Lower_bound
/* documents
   None  (T.T)
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

//Segment tree 2*n code
int n;
int t[maxn * 2 + 10];//segment tree

void build() // O( n )
{
      // Build internal nodes (bottom-up) 
    for(int i = n; i; i--) 
        t[i] = max(t[i*2],t[i*2+1]);
}

  // Update value at position i to val
void up(int i, int val) // O( log(n) )
{
    i += n; // Move to leaf position
    t[i] += val;
      // Update all ancestors of i
    for(i>>=1; i; i >>= 1)
        t[i] = max(t[i*2] , t[i*2+1]);
}

ll cal(int l, int r) 
{
    // bla bla bla , no need here
}
//End Segment tree 2*n code



//Code Walk on Segment Tree 2N
int walk(int val) // Finds the leftmost index with value at least 'val' 
{
    int i = n+1; // go to leaf
    while(t[i] < val && i <= n + n && i > 1)
    {
          // If current position is odd or parent has enough capacity, go right
        if((i & 1) || t[i>>1] >= val)
        {
            i++;
            while(i <= n && t[i] >= val) i <<= 1;
        }
        else i >>= 1; // Go up to parent
    }
    return i - n; // Adjust index to original index of array
}
//End Code Walk on Segment Tree 2N

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/1143
    
    int m;
    cin >> n >> m;
    
    for(int i = 1; i <= n; i++)
    {
        cin >> t[i+n];
    }
    
    build(); 
    
    while(m--)
    {
        int val;
        cin >> val;
        int i = walk(val); // Find suitable index
        if(i < 1) i = 0; // No index found
        cout << i << ' ';
        if(i > 0) up(i, -val); 
    }
    
    return 0;
}