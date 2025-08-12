// Trie 
/*
 https://wiki.vnoi.info/vi/algo/string/trie
*/
// code vnoi chuẩn quá, mình chỉ biết chép :(
// Trie bình thường thì mn dùng array đi, chỉ nên  dùng vector khi thực sự không tính trước được kích thước thôi

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

const int expected_size_per_tree = 1e6 + 10,alphabet = 26; //  expected_size_per_tree = max_size / number_of_trie 

struct Trie
{
  struct Node 
  {
    int child[alphabet];
    int cnt,exist;
    
    Node():cnt(0),exist(0) // constructor 
    {
      memset(child,-1,sizeof(child));
    }
  };
  vector<Node>node;
  Trie()
  {
    node.reserve(expected_size_per_tree); // chuẩn bị trước memory cho vector , đỡ phải realloc 
    node.emplace_back(); // emplace_back sẽ dùng constructor của Node để tạo phần tử thay vì copy 
  }
  
  Trie(int N)
  {
    node.reserve(N); // chuẩn bị trước memory cho vector , đỡ phải realloc 
    node.emplace_back();
  }
  
  int new_node() // Tạo và trả về vị trí của đỉnh mới được tạo ra
  {
    node.emplace_back();
    return node.size()-1;
  }
  
  void add_string(string s)
  {
    int pos = 0;
    for(char k : s)
    {
      int c = k - 'a';
      if(node[pos].child[c] == -1)node[pos].child[c] = new_node();// Nếu cạnh tương ứng chữ cái c chưa tồn tại thì ta tạo ra đỉnh mới
    
      pos = node[pos].child[c];
      node[pos].cnt ++;// Có thêm một xâu trong trie có tiền tố là xâu được thể hiện bằng đỉnh hiện tại
    }
    node[pos].exist++; // Đã tìm được đỉnh tương ứng với xâu s, ta tăng biến exist của đỉnh lên 1
  }
  
  bool find_string(string s)  // Kiểm tra xâu s có trong trie hay không
  {
    int pos = 0;
    for(char k : s)
    {
      int c = k - 'a';
      if(node[pos].child[c] == -1)return 0;
      pos = node[pos].child[c];
    }
    return node[pos].exist != 0;
  }
  
  bool delete_string_recursive(int pos,string &s,int i) // Trả về liệu đỉnh pos có bị xóa đi hay không
  {
    if(i < s.size()) // Nếu chưa đến đỉnh tương ứng với xâu s thì tiếp tục đệ quy xuống dưới
    {
      int c = s[i] - 'a';
      if(delete_string_recursive(node[pos].child[c],s,i+1)) node[pos].child[c] = -1; // Nếu đỉnh con tương ứng bị xóa thì ta gán lại đỉnh tương ứng bằng -1
    }
    else node[pos].exist--; // Nếu đã đến đỉnh tương ứng với xâu s thì ta giảm biến exist của đỉnh
    
    if(pos != 0)node[pos].cnt--; // Nếu đỉnh đang xét không phải gốc cây trie thì ta giảm biến cnt của đỉnh
    
    return node[pos].cnt == 0; //Đỉnh bị xóa nếu không còn xâu nào đi qua nó, nói cách khác là không còn xâu nào có tiền tố là xâu được thể hiện bởi đỉnh pos
  }
  
  void delete_string(string s) 
  {
    if(find_string(s)) delete_string_recursive(0,s,0);
  }
  
  int count_string_with_prefix(string s) // đếm số xâu trong trie có prefix là s
  {
    int pos = 0;
    for(char k : s)
    {
      int c = k - 'a';
      if(node[pos].child[c] == -1)return 0;
      pos = node[pos].child[c];
    }
    return node[pos].cnt;
  }
}trie;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    // https://www.spoj.com/problems/ADAINDEX
    
    int n,m;
    cin>>n>>m;
    while(n--)
    {
      string s;
      cin>>s;
      trie.add_string(s);
    }
    
    while(m--)
    {
      string s;
      cin>>s;
      cout<<trie.count_string_with_prefix(s)<<'\n';
    }
    
    return 0;
}