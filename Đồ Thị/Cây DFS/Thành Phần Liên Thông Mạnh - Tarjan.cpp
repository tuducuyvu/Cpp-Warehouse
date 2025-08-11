//Tarjan
/* documents
https://usaco.guide/adv/SCC?lang=cpp#tarjans-algorithm
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

const int maxn = 1e6 + 10;
vector<int> adj[maxn]; // Đồ Thị (Graph adjacency list)

//Tarjan code
int low[maxn],tim[maxn],t,com; // low[], time[]
stack<int> st;
bool in_stack[maxn];

  // find strongly connected components
void dfs(int i,int pa) // O( n )
{
  low[i] = tim[i] = ++t; // entry time
  st.push(i);
  in_stack[i] = 1; 
  for(int k : adj[i])
  {
    if(tim[k] == 0)
    {
      dfs(k,i);
      low[i] = min(low[i],low[k]); 
    }
    else if(in_stack[k])low[i] = min(low[i],tim[k]); 
  }
  
  if(low[i] == tim[i])// Root of a strongly connected component
  {
    com++;
    cout<<com<<" : ";
    // Pop all nodes in this component from the stack
    while(st.top() != i)
    {
      cout<<st.top()<<' ';
      in_stack[st.top()] = 0;
      st.pop();
    }
    cout<<st.top()<<'\n';
    in_stack[st.top()] = 0;
    st.pop();
  }
}
//End Tarjan code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}