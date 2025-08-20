// Indexable SkipList
/*
  Skiplist là cấu trúc dữ liệu cho phép truy vấn, thêm, xóa phần tử với độ phức tạp trung bình O(log n) giống set (hằng số của skiplist cũng...khá ok).
  Đặc biệt có thể truy cập theo vị trí (index) và truy vấn số lượng phần tử nhỏ hơn giá trị cho trước (order_of_key).
  Tham khảo:
    - https://wiki.vnoi.info/algo/data-structures/Skip-Lists
    - https://codeforces.com/blog/entry/13218
    - https://cgi.di.uoa.gr/~k08/manolis/2024-2025/lectures/skip_list_cookbook.pdf
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

// Indexable SkipList Code
const int maxlog = 19;// Số lượng mức (level) tối đa của skiplist

struct Skiplist
{
    struct Column
    {
        int val; // Giá trị lưu ở node này

        struct Cell
        {
            Column *next; // Con trỏ tới node sau ở cùng level
            int dist_next; // Khoảng cách tới node sau

              // Constructor mặc định
            Cell(): next(nullptr), dist_next(0) {}

              // Constructor với tham số
            Cell(Column *A, int B): next(A), dist_next(B) {}
        };

        vector<Cell> cells; // Mỗi node có một mảng cell tương ứng với các level

          // Constructor: dự trù số lượng cell (level) của node này
        Column(int expected_cells_size = 3)
        {
            cells.reserve(expected_cells_size);// Chỉ reserve dung lượng, chưa tạo phần tử thật sự
        }
    } *begin, *end; // Node đầu và cuối đặc biệt của skiplist (cho tiện xử lí)

    int sz; // Số lượng phần tử thực sự trong skiplist (không tính begin, end)
    
      // Construct skiplist rỗng, tạo node begin và end
    void setup()
    {
        sz = 0;
        begin = new Column(maxlog); // Node bắt đầu, giá trị -1
        end = new Column(maxlog);   // Node kết thúc, giá trị -1
        begin->val = -1;
        end->val = -1;
          // Tạo maxlog phần tử bằng constructor tham số của Cell 
        begin->cells.resize(maxlog, Column::Cell(end, 1));// Mỗi level của begin trỏ đến end, khoảng cách là 1
        end->cells.resize(maxlog, Column::Cell(nullptr, 0));
    }

      // Hàm xóa toàn bộ phần tử skiplist, giải phóng bộ nhớ (để ko bị memory-leak)
    void delete_all()
    {
        Column* pos = begin;
        Column* nxt;
        while (pos != end)
        {
            nxt = pos->cells[0].next; 
            delete pos;
            pos = nxt;
        }
          
        delete end;// Xóa node end cuối cùng
        sz = 0; //reset lại số phần tử 
    }
    
      // Hàm clear thân thuộc 
    void clear()
    {
        delete_all();
        setup();
    }
    
      // Constructor, khởi tạo skiplist rỗng
    Skiplist()
    {
        setup();
    }

      // Destructor, giải phóng bộ nhớ
    ~Skiplist()
    {
        delete_all();
    }

      // Kiểm tra skiplist có rỗng không
    bool empty()
    {
        return sz == 0;
    }

      // Lấy số lượng phần tử trong skiplist
    int size()
    {
        return sz;
    }

      // Tìm node lớn nhất có giá trị < val (dùng cho lower_bound)
    Column* highest_lower_bound(int val)
    {
        Column *pos = begin;
          // Duyệt từ level cao nhất xuống thấp nhất
        for(int i = maxlog-1; i >= 0; i--)
        {
            while(pos->cells[i].next != end && pos->cells[i].next->val < val)
                pos = pos->cells[i].next;
        }
        return pos;
    }
    
    
    /*
    Cho những ai hông hiểu tại sao mình không check pos->cells.size() lúc duyệt qua pos->cells[i].next mà lại không bị out_of_bound / segmentation_fault :
      Nếu như bằng 1 cách nào đó bạn đi được đến node pos thì:
    => Có liên kết từ 1 node bất kì đến pos trên level cao hơn hoặc bằng i
      Mà để một node bất kì có liên kết đến pos trên level i thì pos->cells.size() phải lớn hơn hoặc bằng i 
    => ko bị bug :D 
    */
    
      // Tìm node nhỏ nhất có giá trị >= val
    Column* lower_bound(int val)
    {
        return highest_lower_bound(val)->cells[0].next;
    }
    
      // Tìm node lớn nhất có giá trị <= val
    Column* highest_upper_bound(int val)
    {
        Column *pos = begin;
        for(int i = maxlog-1; i >= 0; i--)
        {
            while(pos->cells[i].next != end && pos->cells[i].next->val <= val)
                pos = pos->cells[i].next;
        }
        return pos;
    }

      // Tìm node nhỏ nhất có giá trị > val
    Column* upper_bound(int val)
    {
        return highest_upper_bound(val)->cells[0].next;
    }
    
      // Kiểm tra giá trị val có tồn tại trong skiplist không
    bool exist(int val)
    {
        Column *pos = lower_bound(val);
        return pos != end && pos->val == val;
    }

      // Tìm giá trị ở vị trí idx (index tính từ 1), lưu kết quả vào ans
      // Trả về true nếu tìm thấy, false nếu idx vượt quá số lượng phần tử
    bool find_by_order(int idx, int &ans)
    {
        if(idx > sz || idx <= 0) return 0;

        Column *pos = begin;
        int tmp = 0;
        
        for(int i = maxlog-1; i >= 0; i--)
        {
            while(tmp + pos->cells[i].dist_next <= idx && pos->cells[i].next != end)
            {
                tmp += pos->cells[i].dist_next;
                pos = pos->cells[i].next;
            }
        }
        ans = pos->val;
        return 1;
    }
    
      // Trả về số lượng phần tử nhỏ hơn val
    int order_of_key(int val)
    {
        int ans = 0;
        Column *pos = begin;
        for(int i = maxlog-1; i >= 0; i--)
        {
            while(pos->cells[i].next != end && pos->cells[i].next->val < val)
            {
                ans += pos->cells[i].dist_next;
                pos = pos->cells[i].next;
            }
        }
        return ans;
    }

      // Sinh ngẫu nhiên số level cho node mới
    int random_level()
    {
        int lvl = 1;
          // Dùng tỉ lệ 50/50 để xác định có lên level tiếp không
        while ((rand() & 1) && lvl < maxlog) lvl++;
        return lvl;
    }

      // Thêm giá trị val vào skiplist (nếu chưa tồn tại)
    void insert(int val)
    {
        if(exist(val)) return; // Nếu đã tồn tại thì không insert  nữa

        int lvl = random_level(); // Số level của node mới
        Column *new_column = new Column(lvl); // Tạo node mới
        new_column->cells.resize(lvl); // tạo lvl phần tử mới bằng constructor mặc định của Cell 
        new_column->val = val;

        Column *pos = begin; // vị trí của phần tử đứng trước new_column trong mỗi level 
        int pos_idx = 0;
        int new_idx = order_of_key(val)+1; // Chỉ số vị trí mới ( của new_column)

          // Duyệt từ level cao xuống thấp, tìm vị trí chèn
        for(int i = maxlog-1; i >= 0; i--)
        {
            while(pos->cells[i].next != end && pos->cells[i].next->val < val)
            {
                pos_idx += pos->cells[i].dist_next;
                pos = pos->cells[i].next;
            }

            if(i < new_column->cells.size())
            {
                  // Tạo liên kết 
                Column* next_pos = pos->cells[i].next; // vị trí của phần tử (sẽ) đứng sau new_column 

                pos->cells[i].next = new_column;
                new_column->cells[i].next = next_pos;

                  // Cập nhật khoảng cách
                int next_pos_idx = pos_idx + pos->cells[i].dist_next + 1;

                pos->cells[i].dist_next = new_idx - pos_idx;
                new_column->cells[i].dist_next = next_pos_idx - new_idx;
            }
            else // Nếu new_column  không có level i, chỉ tăng khoảng cách giữa phần tử trước và sau new_column 
            {
                pos->cells[i].dist_next++;
            }
        }
        sz++; // Tăng size
    }
    
      // Xóa giá trị val khỏi skiplist (nếu tồn tại)
    void erase(int val)
    {
        Column *del_column = lower_bound(val), *pos = begin;
        if(del_column->val != val) return; // Không tồn tại thì thôi

          // Duyệt từ level cao xuống thấp, loại bỏ node
        for(int i = maxlog-1; i >= 0; i--)
        {
            while(pos->cells[i].next != end && pos->cells[i].next->val < val)
                pos = pos->cells[i].next;

            if(pos->cells[i].next == del_column) // có liên kết trực tiếp từ pos đến del_column 
            {
                  // Cập nhật con trỏ và khoảng cách cho node trước và sau
                pos->cells[i].next = del_column->cells[i].next;
                
                pos->cells[i].dist_next = pos->cells[i].dist_next + del_column->cells[i].dist_next - 1;
            }
            else// Nếu liên kết đến node tiếp theo đi vòng qua vị trí của node bị xóa, chỉ giảm khoảng cách chứ ko sửa liên kết 
            {
                pos->cells[i].dist_next--;
            }
        }

        delete del_column; // Giải phóng bộ nhớ node bị xóa
        sz--; // giảm size
    }
}  s ;
// End Indexable SkipList Code

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    // https://www.spoj.com/problems/ORDERSET
    
    int n;
    cin >> n;
    while(n--)
    {
        char ch;
        int i;
        cin >> ch >> i;
        if(ch == 'I')
        {
            // Thêm giá trị i
            s.insert(i);
        }
        else if(ch == 'D')
        {
            // Xóa giá trị i
            s.erase(i);
        }
        else if(ch == 'K')
        {
            // Truy vấn giá trị ở vị trí thứ i
            int ans;
            if(s.find_by_order(i, ans))
            {
                cout << ans << '\n';
            }
            else cout << "invalid\n";
        }
        else
        {
            // Truy vấn số lượng phần tử nhỏ hơn i
            cout << s.order_of_key(i) << '\n';
        }
    }

    return 0;
}
