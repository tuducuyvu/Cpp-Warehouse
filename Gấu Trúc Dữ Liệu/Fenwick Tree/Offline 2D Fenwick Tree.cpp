// Offline 2D BIT
/* documents
  https://usaco.guide/plat/2DRQ?lang=cpp#offline-2d-bit
  https://leduythuccs.github.io/2019-05-30-k-thu-t-n-n-c-y-bit2d/
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

void filter(vector<int> & v) // O( size*log(size) )
{
    sort(all(v));
    v.resize(unique(all(v))-v.begin());
}

int get_compress(int val,const vector<int> & v) // O( log(size) )
{
    return upper_bound(all(v),val)-v.begin();
}

// Code Offline 2D BIT
struct offline_2D_BIT
{
    static const int max_sz = maxn * 2; // largest number of distinct x-coordinate from updates
    vector<int> v[max_sz];
    vector<ll> bit[max_sz];
    
      // reserve coordinates
    void fake_up(int i,int j) // O( log(i) )
    {
        for(;i<max_sz;i+=i&-i) v[i].pb(j);
    }
    
      // Prepare BIT structures after collecting all update-coordinates
    void prepare() // O( max_sz*log(max_sz) )
    {
        for(int i = 1;i<max_sz;i++)
        {
            filter(v[i]);
            bit[i].resize(v[i].size() + 1); // Resize BIT for this row
        }
    }
    
    void up(int i,int J,int val) // O( log(i) * log(j) )
    {
        for(;i<max_sz;i+=i&-i)
            for(int j = get_compress(J,v[i]); j<=v[i].size(); j+=j&-j) 
                bit[i][j] += val;
    }
    
    ll cal(int i,int J) // O( log(i) * log(j) )
    {
        ll ans = 0;
        for(;i;i-=i&-i)
            for(int j = get_compress(J,v[i]); j; j-=j&-j) 
                ans += bit[i][j];
        return ans;
    }
    
      // Calculate sum in rectangle (x,X] * (y,Y]
    ll area(int x,int y,int X,int Y) // O( log(X) * log(Y) * 4 )
    {
        return cal(X,Y) - cal(x,Y) - cal(X,y) + cal(x,y);
    }
};
// End Code Offline 2D BIT

int a[maxn][3]; 
int b[maxn][5]; 

vector<int> coord; 

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://judge.yosupo.jp/problem/point_add_rectangle_sum
    
    int n,m;
    cin>>n>>m;
    
    offline_2D_BIT tree;
    
    for(int i = 1;i<=n;i++)
    {
        for(int j = 0;j<3;j++)cin>>a[i][j];
        a[i][0]++; // avoid 0-indexing
        a[i][1]++;
        coord.pb(a[i][0]); // Collect x-coordinates for compression
    }
    
    for(int i = 1;i<=m;i++)
    {
        cin>>b[i][0]; 
        if(b[i][0] == 0) // Update query
        {
            for(int j = 1;j<4;j++) cin>>b[i][j]; 
            b[i][1]++;
            b[i][2]++;
            coord.pb(b[i][1]);
        }
        else // Sum query
            for(int j = 1;j<5;j++) cin>>b[i][j]; // Read x1, y1, x2, y2
    }
      
      // Compress coordinates
    filter(coord);
    
    for(int i = 1;i<=n;i++)
    {
        a[i][0] = get_compress(a[i][0],coord); // Compress x-coordinate
        tree.fake_up(a[i][0],a[i][1]); // reserve this update in BIT
    }
    
    for(int i = 1;i<=m;i++)
    {
        if(b[i][0] == 0)
        {
            b[i][1] = get_compress(b[i][1],coord); 
            tree.fake_up(b[i][1],b[i][2]); // reserve in BIT
        }
        else 
        {
            b[i][1] = get_compress(b[i][1],coord); // Compress x1
            b[i][3] = get_compress(b[i][3],coord); // Compress x2
        }
    }
    
      // We have reserved all of the updates, now prepare BIT for queries
    tree.prepare();
    
      // Add initial points to BIT
    for(int i = 1;i<=n;i++)
    {
        tree.up(a[i][0],a[i][1],a[i][2]); 
    }
    
    for(int i = 1;i<=m;i++)
    {
        if(b[i][0] == 0) tree.up(b[i][1],b[i][2],b[i][3]); // Real Update :)
        
        else cout << tree.area(b[i][1] , b[i][2] , b[i][3] , b[i][4])<<'\n'; 
    }
    
    return 0;
}
