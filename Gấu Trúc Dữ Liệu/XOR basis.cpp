// XOR basis
/* documents
  https://usaco.guide/adv/xor-basis?lang=cpp
  https://codeforces.com/blog/entry/68953
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

// XOR basis code
struct XORbasis
{
    vector<ll> vec; // our basis :D
      
      // Reduce a number by XORing it with the basis elements
      // This function finds the minimum representation of a number in the basis
      // sometime called this "bitwise Gaussian Elimination"  :P
    ll reduce(ll tmp) // O( log(max_value) )
    {
        for(const ll & k : vec)tmp = min(tmp,tmp^k);
        return tmp;
    }
      
      // Add a number to the XOR basis
    void add(ll tmp) // O( log(max_value) )
    {
        tmp = reduce(tmp);
        if(tmp) vec.pb(tmp);
    }
    
      // Merge two XOR bases together  (Modifies this basis)
    void operator += (const XORbasis & o) // O( log(max_value) ^ 2 )
    {
        for(const ll &k : o.vec) add(k);
    }
    
      // Creates a new basis that contains all elements from both bases
    XORbasis operator + (const XORbasis & o) // O( log(max_value) ^ 2 )
    {
        XORbasis ans = *this;
        ans += o;
        return ans;
    }
      
      // Return the size of the basis
    ll size()  {  return vec.size();  }
    
      // Find the maximum XOR value that can be obtained from the basis
      // This is done by greedily
    ll max_xor() // O( log(max_value) )
    {
        ll ans = 0;
        for(const ll &k : vec)ans = max(ans,ans^k);
        return ans;
    }
};
//End XOR basis code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/3191/
    
    XORbasis b;
    int n;
    cin>>n;
    
    while(n--)
    {
        ll tmp;
        cin>>tmp;
        b.add(tmp);
    }
    
    cout<<b.max_xor();
    
    return 0;
}
