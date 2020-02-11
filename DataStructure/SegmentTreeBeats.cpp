#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> P;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
// #define int long long
#define pb push_back
#define mp make_pair
#define eps 1e-9
#define INF 2000000000 //2e9
#define LLINF 1000000000000000000ll // 1e18
#define fi first
#define sec second
#define all(x) (x).begin(),(x).end()
#define sq(x) ((x)*(x))
#define dmp(x) cerr << #x << ": " << x << endl;

template<class T> void chmin(T& a,const T& b){if(a>b)a=b;}
template<class T> void chmax(T& a,const T& b){if(a<b)a=b;}

template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T,vector<T>,greater<T>>;
template<class T> vector<T> vect(int len,T elem){ return vector<T>(len,elem); }

template<class T,class U>
ostream& operator << (ostream& os,const pair<T,U>& p){
  os << p.fi << ',' << p.sec; return os;
}
template<class T,class U>
istream& operator >> (istream& is,pair<T,U>& p){
  is >> p.fi >> p.sec; return is;
}
template<class T>
ostream& operator << (ostream &os,const vector<T> &vec){
  for(int i=0;i<vec.size();i++){
    os << vec[i];
    if(i+1<vec.size())os << ' ';
  }
  return os;
}
template<class T>
istream& operator >> (istream &is,vector<T>& vec){
  for(int i=0;i<vec.size();i++)is >> vec[i];
  return is;
}
void fastio(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  cout<<fixed<<setprecision(20);
}

// verified https://judge.yosupo.jp/submission/3622

template<class D>
struct SegmentTreeBeats{
  using DMerger = function<D(D,D)>;
  vector<D> seg;
  int length;
  DMerger dm;
  D d_unit;
  SegmentTreeBeats(const vector<D>& vec,DMerger dm,D d_unit = D()):length(1),dm(dm){
    while(length<vec.size())length <<= 1;
    seg.assign(length*2,d_unit);
    for(int i=0;i<vec.size();i++){
      seg[i+length-1] = vec[i];
    }
    for(int i=length-2;i>=0;i--){
      seg[i] = dm(seg[i*2+1],seg[i*2+2]);
    }
  }
  template<class F,class... Args>
  void update(int a,int b,int k,int l,int r,F break_or_puttag,Args... args){
    if(r<=a||b<=l)return;
    if(a<=l&&r<=b&&(seg[k].*break_or_puttag)(args...))return;
    seg[k].pushdown(seg[k*2+1],seg[k*2+2]);
    update(a,b,k*2+1,l,(l+r)/2,break_or_puttag,args...);
    update(a,b,k*2+2,(l+r)/2,r,break_or_puttag,args...);
    seg[k] = dm(seg[k*2+1],seg[k*2+2]);
  }
  template<class F,class... Args>
  void update(int a,int b,F break_or_puttag,Args... args){
    update(a,b,0,0,length,break_or_puttag,args...);
  }
  template<class Getter,class QMerger,class Q>
  Q query(int a,int b,int k,int l,int r,Getter getter,QMerger qm,Q q_unit){
    if(r<=a||b<=l)return q_unit;
    if(a<=l&&r<=b)return (seg[k].*getter)();
    seg[k].pushdown(seg[k*2+1],seg[k*2+2]);
    Q lch = query(a,b,k*2+1,l,(l+r)/2,getter,qm,q_unit);
    Q rch = query(a,b,k*2+2,(l+r)/2,r,getter,qm,q_unit);
    return qm(lch,rch);
  }
  template<class Getter,class QMerger,class Q>
  Q query(int a,int b,Getter getter,QMerger qm,Q q_unit){
    return query(a,b,0,0,length,getter,qm,q_unit);
  }
};

// requirements :
// 
// static Data merge(Data l,Data r)
//
// void pushdown(Data& l,Data& r) (push down tag)
// 
// for each update query :
// bool break_or_puttag_[QUERY] (TAGTYPE tag)
//   if puttag condition is satisfied, update data and put tag
//   return : if break condition or puttag condition is satisfied, return true, otherwise return false

struct Data{
  ll tag,num,sum,mx,mi,second_mx,second_mi,mx_num,mi_num;
  Data(ll v = 0ll):tag(0ll),num(1ll),sum(v),mx(v),mi(v),second_mx(-LLINF),second_mi(LLINF),mx_num(1),mi_num(1){}
  static Data merge(Data l,Data r){
    Data ret;
    ret.tag = 0;
    ret.sum = l.sum+r.sum;
    ret.num = l.num+r.num;

    if(l.mx < r.mx){
      ret.mx = r.mx;
      ret.mx_num = r.mx_num;
      ret.second_mx = max(l.mx,r.second_mx);
    }else if(l.mx > r.mx){
      ret.mx = l.mx;
      ret.mx_num = l.mx_num;
      ret.second_mx = max(l.second_mx,r.mx);
    }else{
      ret.mx = l.mx;
      ret.mx_num = l.mx_num + r.mx_num;
      ret.second_mx = max(l.second_mx,r.second_mx);
    }

    if(l.mi < r.mi){
      ret.mi = l.mi;
      ret.mi_num = l.mi_num;
      ret.second_mi = min(l.second_mi,r.mi);
    }else if(l.mi > r.mi){
      ret.mi = r.mi;
      ret.mi_num = r.mi_num;
      ret.second_mi = min(l.mi,r.second_mi);
    }else{
      ret.mi = l.mi;
      ret.mi_num = l.mi_num + r.mi_num;
      ret.second_mi = min(l.second_mi,r.second_mi);
    }
    return ret;
  }
  bool add(ll x){
    sum += num*x;
    mx += x;
    if(second_mx!=-LLINF)second_mx += x;
    mi += x;
    if(second_mi!=LLINF)second_mi += x;
    tag += x;
    return true;
  }
  void pushdown(Data& l,Data& r){
    l.add(tag);
    r.add(tag);
    tag = 0ll;
    l.chmin_query(mx);
    r.chmin_query(mx);
    l.chmax_query(mi);
    r.chmax_query(mi);
  }
  bool chmax_query(ll x){
    if(mi>=x)return true;
    if(second_mi>x){
      if(second_mi==LLINF){ // 1 value only
        mx = x;
      }else if(second_mi==mx){ // 2 value only
        second_mx = x;
      }
      sum += (x-mi)*mi_num;
      mi = x;
      return true;
    }
    return false;
  }
  bool chmin_query(ll x){
    if(mx<=x)return true;
    if(second_mx<x){
      if(second_mx==-LLINF){ // 1 value only
        mi = x;
      }else if(second_mi==mx){ // 2 value only
        second_mi = x;
      }
      sum -= (mx-x)*mx_num;
      mx = x;
      return true;
    }
    return false;
  }
  ll get_sum(){ return sum; }
  ll get_min(){ return mi; }
  ll get_max(){ return mx; }
};

void yosupo_RangeChminChmaxAddRangeSum(){
  int n,q;
  cin >> n >> q;
  vector<Data> vec;
  for(int i=0;i<n;i++){
    ll a;
    cin >> a;
    vec.emplace_back(a);
  }
  SegmentTreeBeats<Data> seg(vec,Data::merge);
  for(int i=0;i<q;i++){
    int type,l,r;
    ll b;
    cin >> type;
    if(type==0){
      cin >> l >> r >> b;
      seg.update(l,r,&Data::chmin_query,b);
    }
    if(type==1){
      cin >> l >> r >> b;
      seg.update(l,r,&Data::chmax_query,b);
    }
    if(type==2){
      cin >> l >> r >> b;
      seg.update(l,r,&Data::add,b);
    }
    if(type==3){
      cin >> l >> r;
      cout << seg.query(l,r,&Data::get_sum,[](ll x,ll y){return x+y;},0ll) << endl;
    }
    /*
    for(int j=0;j<seg.seg.size();j++){
      cout << "id : " << j << endl;
      cout << " mx : " << seg.seg[j].mx;
      cout << " second_mx : " << seg.seg[j].second_mx;
      cout << " mx_num : " << seg.seg[j].mx_num;
      cout << " mi : " << seg.seg[j].mi;
      cout << " second_mi : " << seg.seg[j].second_mi;
      cout << " mi_num : " << seg.seg[j].mi_num;
      cout << " sum : " << seg.seg[j].sum;
      cout << " num : " << seg.seg[j].num;
      cout << " tag : " << seg.seg[j].tag;
      cout << endl;
    }
    */
  }
}

/* TLE torenai */
void HDU5306_GorgeousSequnence(){
  int t;
  scanf("%d",&t);
  for(int T=0;T<t;T++){
    int n,m;
    // cin >> n >> m;
    scanf("%d %d",&n,&m);
    vector<Data> a;
    for(int i=0;i<n;i++){
      ll x;
      // cin >> x;
      scanf("%lld",&x);
      a.emplace_back(x); 
    }
    SegmentTreeBeats<Data> seg(a,Data::merge);
    for(int i=0;i<m;i++){
      int type,x,y,t;
      // cin >> type;
      scanf("%d",&type);
      if(type==0){
        // cin >> x >> y >> t;
        scanf("%d %d %d",&x,&y,&t);
        x--;
        seg.update(x,y,&Data::chmin_query,t);
      }
      if(type==1){
        // cin >> x >> y;
        scanf("%d %d",&x,&y);
        x--;
        printf("%lld\n",seg.query(x,y,&Data::get_max,[](ll x,ll y){return max(x,y);},-LLINF));
      }
      if(type==2){
        // cin >> x >> y;
        scanf("%d %d",&x,&y);
        x--;
        printf("%lld\n",seg.query(x,y,&Data::get_sum,[](ll x,ll y){return x+y;},0ll));
      }
    }
  }
  return;
}

void AOJ_DSL_2_F(){
  int n,q;
  cin >> n >> q;
  vector<Data> vec(n,Data(2147483647));
  SegmentTreeBeats<Data> seg(vec,Data::merge);
  for(int i=0;i<q;i++){
    int type,l,r,x;
    cin >> type;
    if(type==0){
      cin >> l >> r >> x; seg.update(l,r+1,&Data::chmax_query,1000000000000ll);
      seg.update(l,r+1,&Data::chmin_query,x);
    }
    if(type==1){
      cin >> l >> r;
      cout << seg.query(l,r+1,&Data::get_min,[](ll x,ll y){return min(x,y);},LLINF) << endl;
    }
  }
}

void AOJ_DSL_2_G(){
  int n,q;
  cin >> n >> q;
  vector<Data> vec(n);
  SegmentTreeBeats<Data> seg(vec,Data::merge);
  for(int i=0;i<q;i++){
    int type,l,r,x;
    cin >> type;
    if(type==0){
      cin >> l >> r >> x;
      l--;
      seg.update(l,r,&Data::add,x);
    }
    if(type==1){
      cin >> l >> r;
      l--;
      cout << seg.query(l,r,&Data::get_sum,[](ll x,ll y){return x+y;},0ll) << endl;
    }
  }
}

void AOJ_DSL_2_I(){
  int n,q;
  cin >> n >> q;
  vector<Data> vec(n);
  SegmentTreeBeats<Data> seg(vec,Data::merge);
  for(int i=0;i<q;i++){
    int type,l,r,x;
    cin >> type;
    if(type==0){
      cin >> l >> r >> x;
      seg.update(l,r+1,&Data::chmax_query,2000);
      seg.update(l,r+1,&Data::chmin_query,x);
    }
    if(type==1){
      cin >> l >> r;
      cout << seg.query(l,r+1,&Data::get_sum,[](ll x,ll y){return x+y;},0ll) << endl;
    }
  }
}

void AOJ_DSL_2_H(){
  int n,q;
  cin >> n >> q;
  vector<Data> vec(n);
  SegmentTreeBeats<Data> seg(vec,Data::merge);
  for(int i=0;i<q;i++){
    int type,l,r,x;
    cin >> type;
    if(type==0){
      cin >> l >> r >> x;
      seg.update(l,r+1,&Data::add,x);
    }
    if(type==1){
      cin >> l >> r;
      cout << seg.query(l,r+1,&Data::get_min,[](ll x,ll y){return min(x,y);},LLINF) << endl;
    }
  }
}

signed main(){
  fastio();
  yosupo_RangeChminChmaxAddRangeSum();
  // AOJ_DSL_2_F();
  // AOJ_DSL_2_G();
  // AOJ_DSL_2_I();
  // AOJ_DSL_2_H();
  // HDU5306_GorgeousSequnence();
  return 0;
}
