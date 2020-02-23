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
#define LLINF 2000000000000000000ll // 2e18 (llmax:9e18)
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
namespace Util{
  template<class T>
  vector<pair<T,int>> runLength(vector<T> v){
    vector<pair<T,int>> res;
    for(int i=0;i<v.size();i++){
      if(res.empty()||res.back().first!=v[i])res.push_back(make_pair(v[i],1));
      else res.back().second++;
    }
    return res;
  }
  template<class T>
  void compress(vector<T> &v){
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
  }
}

vector<vector<int>> square(vector<string>& s,char c){
  int n = s.size();
  int m = s[0].size();
  vector<vector<int>> r  = vect(n+1,vect(m+1,0));
  vector<vector<int>> u  = vect(n+1,vect(m+1,0));
  vector<vector<int>> ru = vect(n+1,vect(m+1,0));
  for(int i=n-1;i>=0;i--){
    for(int j=0;j<m;j++){
      if(s[i][j]==c)u[i][j] = u[i+1][j]+1;
      else u[i][j] = 0;
    }
  }
  for(int i=0;i<n;i++){
    for(int j=m-1;j>=0;j--){
      if(s[i][j]==c)r[i][j] = r[i][j+1]+1;
      else r[i][j] = 0;
    }
  }
  for(int i=n-1;i>=0;i--){
    for(int j=m-1;j>=0;j--){
      if(s[i][j]==c)ru[i][j] = min(min(ru[i+1][j+1],r[i][j+1]),u[i+1][j])+1;
      else ru[i][j] = 0;
    }
  }
  return ru;
}

// verified https://codeforces.com/contest/1301/submission/71626156
template<class D>
struct SparseTable2D{
  vector<vector<vector<vector<D>>>> table;
  using DMerger = function<D(D,D)>;
  const DMerger dm;
  SparseTable2D(const vector<vector<D>>& data,const DMerger dm):dm(dm){
    int n = data.size(); assert(n>0);
    int m = data[0].size();
    int logn = 1; while((1<<logn)<n)logn++;
    int logm = 1; while((1<<logm)<m)logm++;
    table = vect(n,vect(logn+1,vect(m,(vector<D>(logm+1)))));
    for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
        table[i][0][j][0] = data[i][j];
      }
    }
    for(int k=1;k<=logm;k++){
      for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
          if(j+(1<<(k-1))<m){
            table[i][0][j][k] = dm(table[i][0][j][k-1],table[i][0][j+(1<<(k-1))][k-1]);
          }else{
            table[i][0][j][k] = table[i][0][j][k-1];
          }
        }
      }
    }
    for(int k=1;k<=logn;k++){
      for(int l=0;l<=logm;l++){
        for(int i=0;i<n;i++){
          for(int j=0;j<m;j++){
            if(i+(1<<(k-1))<n){
              table[i][k][j][l] = dm(table[i][k-1][j][l],table[i+(1<<(k-1))][k-1][j][l]);
            }else{
              table[i][k][j][l] = table[i][k-1][j][l];
            }
          }
        }
      }
    }
  }
  // [x1,x2) [y1,y2)
  // Be careful about order of arguments (x,y,x,y)
  D query(int x1,int y1,int x2,int y2){
    int xlen = x2-x1, ylen = y2-y1;
    if(xlen<=0||ylen<=0)return 0;
    int xd = 0, yd = 0;
    while((1<<(xd+1))<xlen)xd++;
    while((1<<(yd+1))<ylen)yd++;
    D tmp1 = dm(table[x1][xd][y1][yd],table[x2-(1<<xd)][xd][y1][yd]);
    D tmp2 = dm(table[x1][xd][y2-(1<<yd)][yd],table[x2-(1<<xd)][xd][y2-(1<<yd)][yd]);
    return dm(tmp1,tmp2);
  }
};

void solve(){
  int n,m,q;
  cin >> n >> m >> q;
  vector<string> s(n);
  cin >> s;
  auto R = square(s,'R');
  auto B = square(s,'B');
  auto G = square(s,'G');
  auto Y = square(s,'Y');
  vector<vector<int>> nano = vect(n,vect(m,0));
  vector<vector<int>> logo = vect(n,vect(m,0));
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      int cand = R[i][j];
      int ni = i+cand, nj = j+cand;
      if(ni>=n||nj>=m)continue;
      if(R[i][j] <= min(min(Y[ni][j],G[i][nj]),B[ni][nj])){
        nano[i][j] = R[i][j];
      }
    }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      int d = nano[i][j];
      if(d>0)chmax(logo[i+d-1][j+d-1],nano[i][j]);
    }
  }

  // for(auto& r : logo)cout << r << endl;

  SparseTable2D<int> st(logo,[](int a,int b){return max(a,b);});
  
  for(int i=0;i<q;i++){
    int r1,c1,r2,c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--; c1--; r2--; c2--;
    int l = 0, r = 251;
    while(r-l>1){
      int mid = (l+r)/2;
      if(st.query(r1+mid-1,c1+mid-1,r2-mid+1,c2-mid+1)>=mid)l = mid;
      else r = mid;
    }
    cout << l*l*4 << "\n";
  }
  return ;
}
 
signed main(){
  fastio();
  solve();
  // int t; cin >> t; while(t--)solve();
  return 0;
}
