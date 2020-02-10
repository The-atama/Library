#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> P; typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
// #define int long long
#define pb push_back
#define mp make_pair
#define eps 1e-9
#define INF 2000000000 //2e9
#define LLINF 1000000000000000ll // 1e15
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

template<class D>
struct PersistentSegmentTree{

  using DMerger = function<D(D,D)>;
  const DMerger dm;
  const D d_unit;
  int length;

  struct Node {
    D data;
    Node *lch,*rch;
    Node(D data):data(data),lch(nullptr),rch(nullptr){} // Nil leaf node
    Node(Node* lch,Node* rch,const D& data):data(data),lch(lch),rch(rch){}
  };

  PersistentSegmentTree(int length,const DMerger dm,const D& d_unit)
    :length(length),dm(dm),d_unit(d_unit){
  }

  Node* root(){ return nullptr; }

  Node* merge(Node *lch,Node *rch){
    // assert(lch!=nullptr || rch!=nullptr);
    if(lch==nullptr)return new Node(lch,rch,rch->data);
    if(rch==nullptr)return new Node(lch,rch,lch->data);
    return new Node(lch,rch,dm(lch->data,rch->data));
  }

  Node* update(Node* v,int k,const D& x,int l,int r){
    if(r-l==1){
      assert(l==k);
      return new Node(x);
    }else{
      Node *lch,*rch;
      if(k<(l+r)/2){
        lch = update((v==nullptr)?nullptr:v->lch,k,x,l,(l+r)/2);
        rch = (v==nullptr)?nullptr:v->rch;
      }else{
        lch = (v==nullptr)?nullptr:v->lch;
        rch = update((v==nullptr)?nullptr:v->rch,k,x,(l+r)/2,r);
      }
      return merge(lch,rch);
    }
  }

  Node* update(Node* v,int k,const D& x){
    return update(v,k,x,0,length);
  }

  D query(Node* v,int a,int b,int l,int r){
    if(v==nullptr)return d_unit;
    if(r<=a||b<=l)return d_unit;
    if(a<=l&&r<=b)return v->data;
    return dm(query(v->lch,a,b,l,(l+r)/2),query(v->rch,a,b,(l+r)/2,r));
  }

  D query(Node* v,int a,int b){
    return query(v,a,b,0,length);
  }


  void show(Node* v,int depth = 0){
    if(v==nullptr){
      return;
    }
    show(v->lch,depth+1);
    for(int i=0;i<depth;i++)cout << "  ";
    cout << v->data << endl;
    show(v->rch,depth+1);
  }
};

signed main(){
  auto dm = [](int a,int b){return a+b;};
  PersistentSegmentTree<int> seg(4,dm,0);
  auto root = seg.root();
  auto r = seg.update(root,0,3);
  auto r2 = seg.update(r,1,2);
  auto r3 = seg.update(r2,2,4);
  dmp(seg.query(r3,0,2));
  seg.show(r3);
  return 0;
}
