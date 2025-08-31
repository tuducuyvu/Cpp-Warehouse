// Suffix Array
/* documents
  https://cp-algorithms.com/string/suffix-array.html
  https://usaco.guide/adv/suffix-array?lang=cpp
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

const int maxn = 5e5 + 10;

//Suffix Array Code
int suf_arr[maxn];

namespace SuffixArray
{
    int cnt[maxn];
    const int alphabet_size = 300;
    int rank_num;
    int pos[maxn],new_pos[maxn];
    int rank[maxn],new_rank[maxn];
    
      // Performs one step of counting sort and rank updating for the current skip_range
    void build_per_skip(int n,int skip_range) // O( n )
    {
          // Shift positions by skip_range and wrap around
        for(int i = 0;i<n;i++)
        {
            new_pos[i] = pos[i] - skip_range;
            if(new_pos[i] < 0)new_pos[i] += n;
        }
        
          // Count occurrences of each rank
        for(int i = 0;i<=rank_num;i++) cnt[i] = 0;
        
        for(int i = 0;i<n;i++) cnt[rank[new_pos[i]]]++;
        
          // Compute prefix sums for counting sort
        for(int i = 1;i<=rank_num;i++) cnt[i] += cnt[i-1];
        
          // Sort positions according to their rank
        for(int i = n-1;i>=0;i--)
        {
            pos[--cnt[rank[new_pos[i]]]] = new_pos[i];
        }
        
        rank_num = 1; // Start new rank numbers
        new_rank[pos[0]] = 0;
        
          // Assign new ranks for each position
        for(int i = 1;i<n;i++)
        {
            pii A = mk( rank[pos[i]],rank[(pos[i] + skip_range) % n] );
            pii B = mk( rank[pos[i-1]],rank[(pos[i-1] + skip_range) % n] );
            if(A != B)rank_num++;
            new_rank[pos[i]] = rank_num-1;
        }
        
          // Copy new ranks to rank array
        for(int i = 0;i<n;i++) rank[i] = new_rank[i];
    }
    
      // Builds the suffix array for input string s
    void build_suffix_array(const string & s) // O( n * log(n) )
    {
        int n = s.size();
        
          // Initialize positions and ranks by character
        for(int i = 0;i<n;i++)
        {
            pos[i] = i;
            rank[i] = s[i];
        }
        
        rank_num = alphabet_size; // Maximum possible rank
        
        build_per_skip(n,0); // Initial sorting by first character
        
          // Double the skip_range each step to sort by longer prefixes
        for(int skip_range = 1;skip_range < n;skip_range <<= 1)
        {
            build_per_skip(n,skip_range);
        }
        
          // Store final suffix array (excluding '$', which is the first index)
        for(int i = 1;i<n;i++) suf_arr[i-1] = pos[i];
    }
}

//End Suffix Array Code


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://judge.yosupo.jp/problem/suffixarray
    
    string s;
    cin>>s;
      // Add sentinel '$' and build suffix array
    SuffixArray::build_suffix_array(s+'$');
    for(int i = 0;i<s.size();i++)cout<<suf_arr[i]<<' ';
    
    return 0;
}