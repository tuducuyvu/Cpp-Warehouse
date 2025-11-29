// DP 1D1D
/* documents
  https://wiki.vnoi.info/vi/vnoi-magazine/2023/1d1d-dp-optimization
  https://richardyi.ca/blog/1d1d/index.html
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
ll a[maxn], b[maxn], dp[maxn];
int n;

// Dp 1D1D Code 
struct Data
{
    int l, r, opt;
};

ll cost(int l,int r)
{
      // Cost function that satisfy quadrangle inequality ( you can leave the dp[l] outside )
    return dp[l] + b[l] * a[r];
}

struct Container: deque<Data>
{
      // Insert a new candidate segment with opt 'i' and maintain the structure
    void push(int i)
    {
          // Remove segment that are definitely worse than the new one
        while(size() && cost(i, back().l) < cost(back().opt, back().l)) pop_back();
        
        if(size())
        {
            int l = back().l, r = back().r + 1;
            
              // Binary search to find the turning point where new segment is better than last segment
            while(l < r)
            {
                int mid = (l + r)/2;
                if(cost(i, mid) < cost(back().opt, mid)) r = mid;
                else l = mid+1;
            }
            back().r = l-1; // Shrink the last segment

            if(l <= n) push_back({l, n, i}); // New segment
        }
        else push_back({i + 1, n, i});  // If empty, the new segment spans the whole array
    }
    
    ll cal(int i)
    {
        while( front().r < i )pop_front();
        ll ans = cost(front().opt, i);
        
          // If segment range is used up, remove 
        front().l = i+1;
        if(i+1 > front().r) pop_front();
        
        return ans;
    }
};
//End Dp 1D1D Code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    // https://codeforces.com/contest/319/problem/C
    
    cin >> n;
    
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= n; i++) cin>>b[i];
    
    Container container;
    
    container.push(1);  // initialize
    
    for(int i = 2; i <= n; i++)
    {
        dp[i] = container.cal(i); 
        container.push(i);
    }
    
    cout<<dp[n];
    
    return 0;
}
