// Longest Common Prefix
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

const int maxn = 1e5 + 10;

//Longest Common Prefix Code
int suf_arr[maxn];
int lcp[maxn]; // longest common prefix of 2 adjacent suffix in suffix array

namespace SuffixArray
{
    int cnt[maxn];
    const int alphabet_size = 300;
    int rank_num;
    int pos[maxn],new_pos[maxn];
    int rank[maxn],new_rank[maxn];
    
    void build_per_skip(int n,int skip_range)
    {
        for(int i = 0;i<n;i++)
        {
            new_pos[i] = pos[i] - skip_range;
            if(new_pos[i] < 0)new_pos[i] += n;
        }
        
        for(int i = 0;i<=rank_num;i++) cnt[i] = 0;
        
        for(int i = 0;i<n;i++) cnt[rank[new_pos[i]]]++;
        
        for(int i = 1;i<=rank_num;i++) cnt[i] += cnt[i-1];
        
        for(int i = n-1;i>=0;i--)
        {
            pos[--cnt[rank[new_pos[i]]]] = new_pos[i];
        }
        
        rank_num = 1; 
        new_rank[pos[0]] = 0;
        for(int i = 1;i<n;i++)
        {
            pii A = mk( rank[pos[i]],rank[(pos[i] + skip_range) % n] );
            pii B = mk( rank[pos[i-1]],rank[(pos[i-1] + skip_range) % n] );
            if(A != B)rank_num++;
            new_rank[pos[i]] = rank_num-1;
        }
        for(int i = 0;i<n;i++) rank[i] = new_rank[i];
    }
    
    void build_suffix_array(const string & s)
    {
        int n = s.size();
        for(int i = 0;i<n;i++)
        {
            pos[i] = i;
            rank[i] = s[i];
        }
        rank_num = alphabet_size; 
        build_per_skip(n,0); 
        for(int skip_range = 1;skip_range < n;skip_range <<= 1)
        {
            build_per_skip(n,skip_range);
        }
        for(int i = 1;i<n;i++) suf_arr[i-1] = pos[i];
    }
    
    void build_lcp(const string & s) // O( n )
    {
        build_suffix_array(s + '$'); // Build suffix array
        
        int n = s.size();
        
          // store position of each suffix in the suffix array
        for(int i = 0; i < n; i++)  pos[suf_arr[i]] = i;
    
        int k = 0;
          
        for(int i = 0; i < n; i++) // For each suffix in the original string
        {
            if(pos[i] == n-1) // If this is the last suffix, skip (no next suffix to compare)
            {
                k = 0;
                continue;
            }
            int j = suf_arr[pos[i]+1]; // Get the next suffix in lex order
            
              // Count common prefix length between suffixes at i and j
            while(i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
            
            lcp[pos[i]] = k; // Store LCP for this pair
            k = max(k-1, 0); // Reduce k for next iteration (Kasai optimization)
        }
    }
}

//End Longest Common Prefix Code


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://cses.fi/problemset/task/2105
    
    string s;
    cin>>s;
      // Add sentinel '$' and build suffix array
    SuffixArray::build_lcp(s);
    
    ll n = s.size();
    ll ans = n * (n+1) / 2;
    
    for(int i = 0;i<n-1;i++)
    {
        ans -= lcp[i];
    }
    cout<<ans;
    
    return 0;
}