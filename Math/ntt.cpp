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

struct Garner{
  vector<ll> coe;
  vector<ll> p;
  vector<ll> rem;
  ll power_mod(ll x,ll a,ll mod){
    ll res = 1ll;
    while(a>0ll){
      if(a&1)res = (res*x)%mod;
      x = (x*x)%mod;
      a >>= 1;
    }
    return res;
  }
  explicit Garner(vector<ll> &p,vector<ll> &rem):p(p),rem(rem){
    assert(p.size()==rem.size());
    coe.resize(p.size());
    vector<vector<ll>> r(p.size(),vector<ll>(p.size()));
    for(int i=0;i<p.size();i++){
      for(int j=0;j<p.size();j++){
        r[i][j] = power_mod(p[i],p[j]-2ll,p[j]);
      }
    }
    for(int i=0;i<p.size();i++){
      coe[i] = rem[i];
      for(int j=0;j<i;j++){
        coe[i] = r[j][i] * (coe[i]-coe[j]);
        coe[i] = ((coe[i]%p[i])+p[i])%p[i];
      }
    }
  }
  ll get(ll mod) const {
    ll res = 0ll;
    ll base = 1ll;
    for(int i=0;i<p.size();i++){
      res = (res+base*coe[i])%mod;
      base = (base*p[i])%mod;
    }
    return res;
  }
};

template<ll MOD,ll primitive>
class NTT{
public:
  ll power_mod(ll x,ll a,ll mod){
    ll res = 1ll;
    while(a>0ll){
      if(a&1)res = (res*x)%mod;
      x = (x*x)%mod;
      a >>= 1;
    }
    return res;
  }
  ll get_MOD() const { return MOD;}
  vector<ll> dft(vector<ll> f,int n,int sgn=1){
    if(n==1)return f;
    vector<ll> f0,f1;
    for(int i=0;i<n/2;i++){
      f0.pb(f[i*2]);
      f1.pb(f[i*2+1]);
    }
    f0 = dft(f0,n/2,sgn);
    f1 = dft(f1,n/2,sgn);
    ll zeta = power_mod(primitive,(MOD-1ll)/(ll)n,MOD);
    if(sgn==-1)zeta = power_mod(zeta,MOD-2,MOD);
    ll pow_zeta = 1ll;
    for(int i=0;i<n;i++){
      f[i] = (f0[i%(n/2)]+pow_zeta*f1[i%(n/2)])%MOD;
      pow_zeta = (pow_zeta*zeta)%MOD;
    }
    return f;
  }
  vector<ll> idft(vector<ll> f,int n){
    f = dft(f,n,-1);
    ll ninv = power_mod(n,MOD-2,MOD);
    for(int i=0;i<f.size();i++){
      f[i] = (f[i]*ninv)%MOD;
    }
    return f;
  }
  vector<ll> mult(vector<ll> A,vector<ll> B){
    int n = 1;
    while(n<A.size()+B.size()+1)n<<=1;
    A.resize(n,0);
    B.resize(n,0);
    A = dft(A,n);
    B = dft(B,n);
    vector<ll> C;
    for(int i=0;i<n;i++)C.pb((A[i]*B[i])%MOD);
    return idft(C,n);
  }
};

using NTT1 = NTT<469762049ll,3ll>;
using NTT2 = NTT<998244353ll,3ll>;
using NTT3 = NTT<1224736769ll,3ll>;

// for arbitary mod
vector<ll> ConvolutionWithGarner(vector<ll> a,vector<ll> b,ll mod){
  for(ll &x : a) x = ((x%mod)+mod)%mod;
  for(ll &x : b) x = ((x%mod)+mod)%mod;
  NTT1 ntt1; NTT2 ntt2; NTT3 ntt3;
  vector<ll> c1 = ntt1.mult(a,b);
  vector<ll> c2 = ntt2.mult(a,b);
  vector<ll> c3 = ntt3.mult(a,b);
  vector<ll> p = {ntt1.get_MOD(),ntt2.get_MOD(),ntt3.get_MOD()};
  vector<Garner> gn;
  for(int i=0;i<c1.size();i++){
    vector<ll> rem = {c1[i],c2[i],c3[i]};
    gn.push_back(Garner(p,rem));
  }
  vector<ll> c;
  for(int i=0;i<c1.size();i++){
    c.push_back(gn[i].get(mod));
  }
  return c;
}

int main(){
  fastio();
	int N;
	cin >> N;
	vector<ll> A(N+1,0),B(N+1,0);
	for(int i=1;i<=N;i++){
		cin >> A[i] >> B[i];
	}
	//vector<ll> C = ConvolutionWithGarner(A,B,1000000007);
  NTT1 ntt1;
  vector<ll> C = ntt1.mult(A,B);
	for(int i=1;i<=2*N;i++){
		cout << C[i] << endl;
	}
	return 0;
}
