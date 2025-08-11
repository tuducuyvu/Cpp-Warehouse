//matrix
/* documents
https://wiki.vnoi.info/vi/algo/trick/matrix-multiplication
 or wutanhung
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

//matrix code
const int matrix_size = 10,mod = 1e9 + 7;
struct matrix
{
  ll ma[matrix_size][matrix_size];
  
  matrix():ma() // base-case Initialization
  {
    // Initialize all elements to 0
    for(int i = 0;i<matrix_size;i++)
    {
      for(int j = 0;j<matrix_size;j++)
      {
        ma[i][j] = 0;
      }
    }
  };
  
  matrix(bool ch):ma() // Identity Matrix Initialize
  {
    // Initialize as identity matrix if ch is true
    for(int i = 0;i<matrix_size;i++)
    {
      for(int j = 0;j<matrix_size;j++)
      {
        if(i==j)ma[i][j] = 1;
        else ma[i][j] = 0;
      }
    }
  };
  
  matrix operator * (const matrix &o)const
  {
    // matrix multiplication (modulo mod)
    matrix ans;
    for(int i = 0;i<matrix_size;i++)
    {
      for(int j = 0;j<matrix_size;j++)
      {
        for(int k = 0;k<matrix_size;k++)
        {
          ans.ma[i][j] += ma[i][k] * o.ma[k][j];
          ans.ma[i][j] %= mod;
        }
      }
    }
    return ans;
  }
};
//End matrix code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}