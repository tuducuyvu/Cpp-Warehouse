// Manhattan 2D Range Query with Fenwick Tree
/*
    The problem : https://usaco.org/index.php?page=viewproblem2&cpid=416
    
    To transform the original grid, we tilt the grid 45 degree clockwise
    , and separate the odd/even lines into 2 grid 
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

const int val_range = 4e2 * 3 + 10; // val_range = n + k  = n + n*2 = n*3 

//Code Manhattan 2D Range Query with Fenwick Tree
int bit[val_range*2][val_range*2][2];

  // Update the id-th Fenwick Tree at (I, J)
void up(int I,int J,int id,int val)
{
    for(int i = I ; i<val_range*2 ; i+=i&-i)
        for(int j = J; j<val_range*2 ; j+=j&-j) bit[i][j][id]+=val;
}

  // Query the id-th Fenwick Tree prefix sum up to (I, J)
int cal(int I,int J,int id)
{
    int ans = 0;
    for(int i = I ; i; i-=i&-i)
        for(int j = J ; j; j-=j&-j) ans+=bit[i][j][id];
    
    return ans;
}

  // Structure to represent a cell in the transformed coordinate system
struct Cell
{
    int i,j,id; // coordinate and the id-th Fenwick Tree that this Cell belong
    
    Cell(int I,int J,int ID): i(I),j(J),id(ID) {}

      // Shift the cell left by one in the transformed grid
    Cell shift_left() const { return Cell(i,j-1,id); }

      // Shift the cell up by one in the transformed grid
    Cell shift_up() const { return Cell(i-1,j,id); }

      // Query prefix sum at current cell
    int cal_prefix() const { return cal(i,j,id); }

      // Update value at current cell in BIT
    void up_val(int val) { up(i,j,id,val); }
};

  // Convert original (i, j) to transformed coordinates for diamond queries
Cell locate(int i,int j)
{
    int line_id = (i+j);
      // The transformation allows diamond-shaped range queries to be rectangular in new coordinates
    return Cell( line_id / 2 + val_range, j-i + val_range , line_id & 1 );
}

  // Calculates the sum in the diamond region of radius k centered at (i, j)
int area(int i,int j,int k)
{
      // Uses inclusion-exclusion principle on the transformed BIT to get diamond sum
    int ans = locate(i,j+k).cal_prefix();
    ans -= locate(i+k,j).shift_left().cal_prefix();
    ans -= locate(i-k,j).shift_up().cal_prefix();
    ans += locate(i,j-k).shift_left().shift_up().cal_prefix();
    return ans;
}
//End Code Manhattan 2D Range Query with Fenwick Tree

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://usaco.org/index.php?page=viewproblem2&cpid=416
    
    freopen("lazy.in","r",stdin);
    freopen("lazy.out","w",stdout);
    
    int n,k;
    cin>>n>>k;
    
    for(int i = 1;i<=n;i++)
    {
        for(int j = 1;j<=n;j++)
        {
            int val;
            cin>>val;
            locate(i,j).up_val(val);
        }
    }
    
    int ans = 0;
    
    for(int i = 1;i<=n;i++)
    {
        for(int j = 1;j<=n;j++)
        {
              // (!) remember, area(i,j,k) only partially query on 1 Fenwick, add area(i,j,k-1) for the remaining Fenwick
            ans = max(ans, area(i,j,k) + area(i,j,k-1) );
        }
    }
    
    cout<<ans;
    
    return 0;
}