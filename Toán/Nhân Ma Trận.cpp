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
const int mod = 1e9 + 7;
  // Matrix template for fixed size matrix operations
template <int matrix_size> struct matrix
{
    ll ma[matrix_size][matrix_size];
    
      // Constructor
      // If ch == true, initialize as identity matrix,
      // otherwise initialize as zero matrix
    matrix(bool ch)
    {
        for(int i = 0;i<matrix_size;i++)
        {
            for(int j = 0;j<matrix_size;j++)
            {
                if(i==j && ch)ma[i][j] = 1;
                else ma[i][j] = 0;
            }
        }
    };
    
      // Matrix multiplication (modulo mod)
    matrix operator * (const matrix <matrix_size> &o)const
    {
        matrix <matrix_size> ans(0);
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
    
      // Fast matrix exponentiation
      // Raises matrix to the power b
    matrix <matrix_size> power(ll b)
    {
        matrix <matrix_size> ans(1);
        if(b <= 0)return ans;
        matrix <matrix_size> a = *this;
        for(;b;b>>=1)
        {
            if(b&1)ans = ans * a;
            a = a * a;
        }
        return ans;
    }
    
      // Print matrix to stdout
    void print()
    {
        for(int i = 0;i<matrix_size;i++)
        {
            for(int j = 0;j<matrix_size;j++)
            {
                cout<<ma[i][j]<<' ';
            }
            cout<<'\n';
        }
    }
};
//End matrix code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/1722
    ll n;
    cin>>n;
    
    matrix <2> a(0),b(0);
    
      // a is used as the initial vector in matrix exponentiation
    a.ma[0][1] = 1;
    
      // b is the transformation matrix for Fibonacci sequence
    b.ma[0][1] = b.ma[1][0] = b.ma[1][1] = 1;
    
      // Calculate n-th Fibonacci number using matrix exponentiation
    cout<<(a * b.power(n)).ma[0][0];
    
    return 0;
}
