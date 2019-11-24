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
template<class T>
void dump(vector<T> &vec){
	for(int i=0;i<vec.size();i++){
		cout << vec[i];
		if(i+1<vec.size())cout << ' ';
		else cout << endl;
	}
	return;
}
template<class T>
void input(vector<T>& vec,int n){
	vec.resize(n);
	for(int i=0;i<n;i++){
		cin >> vec[i];
	}
}
// verifyed EDPC Z
// https://atcoder.jp/contests/dp/tasks/dp_z
// Comptype true : min, false : max
template<class T,bool Comptype = true>
struct LiChaoTree{
	using Line = pair<T,T>;	
	int sz = 1;
	vector<Line> seg;
	vector<T> xs;
	LiChaoTree(){}
	void init(vector<T>& x,T id){
		xs = x;
		int n = x.size();
		while(sz<n)sz<<=1;
		xs.resize(sz,x.back());
		seg.resize(sz*2,Line(T(0),id));
	}
	void dump_tree(){
		for(int i=0;i<seg.size();i++){
			cout << i << ':' << seg[i].fi << ' ' << seg[i].sec << endl;
		}
		// dump(xs);
	}
	static inline T f(Line l,ll x){
		return l.fi*x+l.sec;
	}	
	void add(Line line,int k,int l ,int r){
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
				add(line,2*k+1,l,mid);
			}else{
				add(line,2*k+2,mid,r);
			}
		}
	}
	void add(Line line){
		add(line,0,0,sz);
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
int main(){
	int N;
	ll C;
	vector<ll> h;
	LiChaoTree<ll> seg;
	vector<ll> dp;
	cin >> N >> C;
	input(h,N);
	dp.resize(N,0ll);
	seg.init(h,LLINF);
	seg.add(make_pair(-2*h[0],dp[0]+h[0]*h[0]));
	for(int i=1;i<N;i++){
		// seg.dump_tree();
		dp[i] = h[i]*h[i]+C+seg.query(i);
		// cout << i << ' ' << dp[i] << endl;
		seg.add(make_pair(-2ll*h[i],h[i]*h[i]+dp[i]));
	}
	cout << dp[N-1] << endl;
	return 0;
}
