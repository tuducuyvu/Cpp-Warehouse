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

const double  pi =acos(-1.0);
template<typename T>
struct point
{
  T x,y;
  
  point():x(0),y(0){}
  point(T x,T y):x(x),y(y){}
  
  point operator + (const point&b)const {return {x + b.x,y + b.y};}
  point operator - (const point&b)const {return {x - b.x,y - b.y};}
  
  bool operator <(const point &b)const {return (x == b.x?y < b.y : x < b.x);}
  bool operator == (const point &b )const {return  x == b.x && y == b.y;}
  bool operator <= (const point& b)const {return *this < b || *this == b;}
  bool operator > (const point& b)const {return !(*this <= b);}
  bool operator >= (const point& b)const {return !(*this < b);}
  bool operator != (const point &b )const {return !(*this == b);}
  
  friend T dot(point a,point b){return a.x * b.x + a.y * b.y;}
  friend T cross(point a,point b){return a.x * b.y - a.y * b.x;}
  friend T len(point a,point b){return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));}
  
  friend bool left(point a,point b,point c){return cross(b - a,c - b) > 0;}
  friend bool right(point a,point b,point c){return cross(b - a,c - b) < 0;}
  friend bool straight(point a,point b,point c){return cross(b - a,c - b) == 0;}
  
  friend istream & operator >> (istream& inp,point& p){return inp>>p.x>>p.y,inp;}
  friend ostream & operator << (ostream& out,const point& p){return out<<p.x<<' '<<p.y,out;}
  
  double angle()
  {
    double ans = atan2(y,x);
    if(ans <0)ans += pi * 2.0;
    return ans;
  }
  double len()
  {
    return sqrt(x * x + y * y);
  }
};

template<typename T>
struct line 
{
  T A,B,C;
  line() : A(0),B(0),C(0){}
  line(T A,T B,T C):A(A),B(B),C(C){}
  line(point<T> a,point<T> b): A(b.y - a.y),B(a.x - b.x), C(cross(a,b)){}
  
  line fix()
  {
    T g = __gcd(A,__gcd(B,C));
    line<T> res(A/g,B/g,C/g);
    if(res.A < 0 || (res.A == 0 && res.B < 0))res.A = -res.A,res.B = -res.B,res.C = -res.C;
    return res;
  }
  
  line rotate()
  {
    return line<T>(-B,A,C);
  }
  
  line adjust_to(point<T> a)
  {
    return line<T>(A,B,A * a.x + B*a.y);
  }
  
  friend point<T> cut_point(line a,line b)
  {
    T d = cross(point<T>(a.A,b.A),point<T>(a.B,b.B));
    if(d == 0)
    {
      return point<T>(INT_MAX,INT_MAX);
    }
    T x = cross(point<T>(b.B,a.B),point<T>(b.C,a.C))/d;
    T y = cross(point<T>(a.A,b.A),point<T>(a.C,b.C))/d;
    return point<T>(x,y);
  }
  
  friend T sub_point(line a,point<T> b)
  {
    return a.A*b.x + a.B*b.y - a.C;
  }
  
  friend T dis_to_line(line a,point<T> b)
  {
    return abs(sub_point(a,b)) / sqrt(a.A * a.A + a.B * a.B);
  }
  
  T dis_to_ray(point<T> a,point<T> b,point<T>c)
  {
    line<double>d(b,c);
    point<double> e = cut_point(d,d.rotate().adjust_to(a));
    if((e < b) == (b < c))return len(a,b);
    else return len(a,e);
  }
  
  T dis_to_segment(point<T> a,point<T> b,point<T>c)
  {
    line<double>d(b,c);
    point<double> e = cut_point(d,d.rotate().adjust_to(a));
    if((e < b) == (b < c))return len(a,b);
    else if((e < c) == (c < b))return len(a,c);
    else return len(a,e);
  }
  
  friend istream & operator >> (istream &inp,line &l){return inp>>l.A>>l.B>>l.C,inp;}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    
    return 0;
}