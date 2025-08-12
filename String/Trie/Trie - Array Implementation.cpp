// Trie 
/*
 https://wiki.vnoi.info/vi/algo/string/trie
*/
// code vnoi chuẩn quá, nên mình  chỉ thêm hàm reset cho trie trong này thôi 

#include <bits/stdc++.h>

const int NUMBEROFNODES = 1e6+10;
struct Trie{
    struct Node{
        int child[26];
        int exist, cnt;
    } nodes[NUMBEROFNODES];
    
    int cur; // Hiện trong trie đang có bao nhiêu đỉnh
    
    void reset() // reset lại trie cho các bài multitest 
    {
      cur = 0;
      memset(nodes[0].child, -1, sizeof(nodes[cur].child));
      nodes[0].exist = nodes[0].cnt = 0;
    }

    Trie() { 
        reset();
    };
};

int main()
{
  return 0;
}

