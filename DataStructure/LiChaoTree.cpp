#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
typedef pair<P,int> T;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
#define pb push_back
#define mp make_pair
#define eps 1e-9
#define INF 2000000000
#define LLINF 1000000000000000000ll
#define sz(x) ((int)(x).size())
#define fi first
#define sec second
#define all(x) (x).begin(),(x).end()
#define sq(x) ((x)*(x))
#define rep(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define repn(i,a,n) for(int (i)=(a);(i)<(int)(n);(i)++)
#define EQ(a,b) (abs((a)-(b))<eps)
#define dmp(x) cerr << __LINE__ << " " << #x << " " << x << endl;

template<class T> void chmin(T& a,const T& b){if(a>b)a=b;}
template<class T> void chmax(T& a,const T& b){if(a<b)a=b;}

// verifyed EDPC Z
// https://atcoder.jp/contests/dp/tasks/dp_z
// 
// Li Chao Tree
//
// template parameter @ Comptype true : min, false : max
//
// constructor @ x  : coordinate value of x-axis
//               id : initially add line "0*x+id" (LLINF,numeric_limits<ll>::max() etc.[in case of MIN])
// member @
//           add_line    : add line "ax+b"              in O(logN) time
//           add_segment : add segment "ax+b" to [l,r)  in O((logN)^2) time
//

template<class T,bool Comptype = true>
struct LiChaoTree{
	using Line = pair<T,T>;	
	int sz = 1;
	vector<Line> seg;
	vector<T> xs;
	explicit LiChaoTree(vector<T> x,T id):xs(x){
		int n = x.size();
		while(sz<n)sz<<=1;
		xs.resize(sz,x.back());
		seg.assign(sz*2,Line(T(0),id));
	}
	void dump_tree(){
		for(int i=0;i<seg.size();i++){
			cout << i << ':' << seg[i].fi << ' ' << seg[i].sec << endl;
		}
	}
	static inline T f(Line l,ll x){
		return l.fi*x+l.sec;
	}	
	void add_line(Line line,int k,int l ,int r){
		int mid = (l+r)/2;
		T lx = xs[l];
		T mx = xs[mid];
		T rx = xs[r-1];
		bool lb = (f(line,lx)<f(seg[k],lx));
		bool mb = (f(line,mx)<f(seg[k],mx));
		bool rb = (f(line,rx)<f(seg[k],rx));
		if((lb==Comptype)&&(rb==Comptype)){
			seg[k] = line;
			return;
		}else if((lb!=Comptype)&&(rb!=Comptype)){
			return;
		}else{
			if(mb==Comptype)swap(seg[k],line);
			if(lb!=mb){
				add_line(line,2*k+1,l,mid);
			}else{
				add_line(line,2*k+2,mid,r);
			}
		}
	}
	void add_line(Line line){
		add_line(line,0,0,sz);
	}
  void add_segment(Line line,int a,int b,int k,int l,int r){
    if(r<=a||b<=l)return;
    if(a<=l&&r<=b){
      add_line(line,k,l,r);
      return;
    }
    add_segment(line,a,b,k*2+1,l,(l+r)/2);
    add_segment(line,a,b,k*2+2,(l+r)/2,r);
  }
  void add_segment(Line line,int a,int b){
    add_segment(line,a,b,0,0,sz);
  }
	T query(int k){
		T x = xs[k];
		k += sz-1;
		T ret = f(seg[k],x);
		while(k>0){
			k = (k-1)/2;
			T tmp = f(seg[k],x);
			if((tmp<ret)==Comptype)ret = tmp;
		}
		return ret;
	}
};

void EDPC_Z(){
	int N;
	ll C;
	vector<ll> h;
	vector<ll> dp;
	cin >> N >> C;
  for(int i=0;i<N;i++)cin >> h[i];
	dp.resize(N,0ll);
	LiChaoTree<ll> seg(h,LLINF);
	seg.add_line(make_pair(-2*h[0],dp[0]+h[0]*h[0]));
	for(int i=1;i<N;i++){
		// seg.dump_tree();
		dp[i] = h[i]*h[i]+C+seg.query(i);
		// cout << i << ' ' << dp[i] << endl;
		seg.add_line(make_pair(-2ll*h[i],h[i]*h[i]+dp[i]));
	}
	cout << dp[N-1] << endl;
}

// verified https://judge.yosupo.jp/submission/3626
void LineAddGetMin(){
  int N,Q;
  cin >> N >> Q;
  vector<ll> zip;
  vector<ll> A(N),B(N);
  vector<ll> t(Q),a(Q),b(Q),p(Q);
  for(int i=0;i<N;i++)cin >> A[i] >> B[i];
  for(int i=0;i<Q;i++){
    cin >> t[i];
    if(t[i]==0){
      cin >> a[i] >> b[i];
    }else{
      cin >> p[i];
      zip.push_back(p[i]);
    }
  }
  sort(all(zip));
  zip.erase(unique(all(zip)),zip.end());
  LiChaoTree<ll> seg(zip,numeric_limits<ll>::max());
  for(int i=0;i<N;i++){
    seg.add_line(make_pair(A[i],B[i]));
  }
  for(int i=0;i<Q;i++){
    if(t[i]==0){
      seg.add_line(make_pair(a[i],b[i]));
    }else{
      p[i] = lower_bound(all(zip),p[i])-zip.begin();
      cout << seg.query(p[i]) << endl;
    }
  }
}

// verified https://judge.yosupo.jp/submission/3625
void SegmentAddGetMin(){
  int N,Q;
  cin >> N >> Q;
  vector<ll> A(N),B(N),L(N),R(N);
  vector<ll> t(Q),a(Q),b(Q),l(Q),r(Q),x(Q);
  vector<ll> zip;
  for(int i=0;i<N;i++){
    cin >> L[i] >> R[i] >> A[i] >> B[i];
    zip.push_back(L[i]);
    zip.push_back(R[i]);
  }
  for(int i=0;i<Q;i++){
    cin >> t[i];
    if(t[i]==0){
      cin >> l[i] >> r[i] >> a[i] >> b[i];
      zip.push_back(l[i]);
      zip.push_back(r[i]);
    }else{
      cin >> x[i];
      zip.push_back(x[i]);
    }
  }
  sort(all(zip));
  zip.erase(unique(all(zip)),zip.end());
	LiChaoTree<ll> seg(zip,numeric_limits<ll>::max());
  auto idx = [&](ll val){ return lower_bound(all(zip),val)-zip.begin(); };
  for(int i=0;i<N;i++){
    L[i] = idx(L[i]);
    R[i] = idx(R[i]);
    seg.add_segment(make_pair(A[i],B[i]),L[i],R[i]);
  }
  for(int i=0;i<Q;i++){
    if(t[i]==0){
      l[i] = idx(l[i]);
      r[i] = idx(r[i]);
      seg.add_segment(make_pair(a[i],b[i]),l[i],r[i]);
    }else{ 
      x[i] = idx(x[i]);
      ll ans = seg.query(x[i]);
      if(ans==numeric_limits<ll>::max())cout << "INFINITY" << endl;
      else cout << ans << endl;
    }
  }
}

signed main(){
  // EDPC_Z();
  // SegmentAddGetMin();
  LineAddGetMin();
  return 0;
}
