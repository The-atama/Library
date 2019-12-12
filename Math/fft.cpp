#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
#define pb push_back
#define mp make_pair
#define eps 1e-9
#define INF 2000000000
#define LLINF 1000000000000000ll
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
template<class T,class U>
ostream& operator << (ostream& os,pair<T,U>& p){
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
	cout<<fixed<<setprecision(12);
}

// verifyed https://atcoder.jp/contests/atc001/submissions/7586931
using Complex = complex<double>;
vector<Complex> dft(vector<Complex> f,int n,int sgn=1){
  if(n==1)return f;
  vector<Complex> f0,f1;
  for(int i=0;i<n/2;i++){
    f0.pb(f[i*2]);
    f1.pb(f[i*2+1]);
  }
  f0 = dft(f0,n/2,sgn);
  f1 = dft(f1,n/2,sgn);
  Complex zeta = polar(1.0,2.0*M_PI/n*sgn);
  Complex pow_zeta = 1;
  for(int i=0;i<n;i++){
    f[i] = f0[i%(n/2)]+pow_zeta*f1[i%(n/2)];
    pow_zeta *= zeta;
  }
  return f;
}
vector<Complex> idft(vector<Complex> f,int n){
  f = dft(f,n,-1);
  for(int i=0;i<f.size();i++){
    f[i] /= n;
  }
  return f;
}
vector<Complex> mult(vector<Complex> A,vector<Complex> B){
  int n = 1;
  while(n<A.size()+B.size()+1)n<<=1;
  A.resize(n,0);
  B.resize(n,0);
  A = dft(A,n);
  B = dft(B,n);
  vector<Complex> C;
  for(int i=0;i<n;i++)C.pb(A[i]*B[i]);
  return idft(C,n);
}
int main(){
  fastio();
	int N;
	cin >> N;
	vector<Complex> A(N+1,0),B(N+1,0);
	for(int i=1;i<=N;i++){
		cin >> A[i] >> B[i];
	}
	vector<Complex> C = mult(A,B);
	for(int i=1;i<=2*N;i++){
		cout << (int)(C[i].real()+0.5) << endl;
	}
	return 0;
}
