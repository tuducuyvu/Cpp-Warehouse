// Trie 
/*
 https://wiki.vnoi.info/vi/algo/string/trie
*/
// code vnoi chuẩn quá, nên mình  chỉ thêm destructor với hàm reset thôi  ( trong mấy bài multitest dùng sẽ ko bị memory-leak )
// các bạn nên  biết về constructor , destructor và con trỏ trước khi implement code này 
// xem con trỏ trong https://wiki.vnoi.info/vi/languages/cpp/pointers
// (!) các bạn nên dùng nullptr thay cho NULL , hnhu tài liệu hơi cũ
// (!) tốt nhất đừng dùng con trỏ :) bug chết đấy 

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

const int NUMBEROFNODES = 1e6+10;
struct Trie{
    struct Node{
        Node* child[26];
        int exist, cnt;

        Node() { // constructor
            for (int i = 0; i < 26; i++) child[i] = NULL;
            exist = cnt = 0;
        }
        
        ~Node() // destructor
        {
          for(int i = 0;i<26;i++)
          {
            delete child[i];
            child[i] = NULL;
          }
        }
    };

    Node* root;
    Trie() { // constructor
        root = new Node();
    };
    
    ~Trie() // destructor
    {
      delete root;
    }
    
    void reset()
    {
      delete root;
      root = new Node();
    }

    void add_string(string s) {
        Node* p = root;
        for (auto f : s) {
            int c = f - 'a';
            if (p->child[c] == NULL) p->child[c] = new Node();

            p = p->child[c];
            p->cnt++;
        }
        p->exist++;
    }

    bool delete_string_recursive(Node* p, string& s, int i) {
        if (i != (int)s.size()) {
            int c = s[i] - 'a';
            bool isChildDeleted = delete_string_recursive(p->child[c], s, i + 1);
            if (isChildDeleted) p->child[c] = NULL;
        }
        else p->exist--;

        if (p != root) {
            p->cnt--;
            if (p->cnt == 0) {
                delete(p); // Khác với cài đặt bằng mảng,
                           // ta có thể thực sự xóa đỉnh này đi
                return true;
            }
        }
        return false;
    }

    void delete_string(string s) {
        if (find_string(s) == false) return;

        delete_string_recursive(root, s, 0);
    }

    bool find_string(string s) {
        Node* p = root;
        for (auto f : s) {
            int c = f - 'a';
            if (p->child[c] == NULL) return false;
            p = p->child[c];
        }
        return (p->exist != 0);
    }
    
    int count_string_with_prefix(string s)
    {
      Node* p = root;
      for(char k : s)
      {
        int c = k - 'a';
        if(p->child[c] == NULL) return 0;
        p = p->child[c];
      }
      return p->cnt;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    // https://www.spoj.com/problems/ADAINDEX
    Trie trie;
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