// Gosper's Hack
/* documents
  https://programmingforinsomniacs.blogspot.com/2018/03/gospers-hack-explained.html
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


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // Gosper's Hack : iterate over masks that have exactly K bit 1
    
    int n,k;
    cin>>n>>k;
    
    for(int mask = (1<<k)-1; mask < (1<<n); )
    {
        cout<<bitset<31>(mask)<<'\n';
        
        int c = mask&-mask;
        int f = mask + c;
        mask = ((((mask^f)>>2)/c)|f); // crazy
    }
    
    return 0;
}