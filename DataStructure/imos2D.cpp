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
#define sz(x) ((int)(x).size())
#define fi first
#define sec second
#define all(x) (x).begin(),(x).end()
#define sq(x) ((x)*(x))
#define rep(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define repn(i,a,n) for(int (i)=(a);(i)<(int)(n);(i)++)
#define EQ(a,b) (abs((a)-(b))<eps)
template<class T> void chmin(T& a,const T& b){if(a>b)a=b;}
template<class T> void chmax(T& a,const T& b){if(a<b)a=b;}
struct imos2D{
	vector<vector<int> > f;
	vector<vector<int> > rui;
	bool flag;
	imos2D(){
		flag = false;
	}
	imos2D(int H,int W){
		flag = false;
		f.resize(H);
		for(int i=0;i<H;i++)f[i].resize(W);
	}
	void set(int x,int y,int v){
		assert(x<f.size()&&y<f[0].size());
		assert(!flag);
		f[x][y]=v;
	}
	void calc(){
		rui = f;
		for(int i=0;i<f.size();i++){
			for(int j=1;j<f[0].size();j++){
				rui[i][j]+=rui[i][j-1];
			}
		}
		for(int i=1;i<f.size();i++){
			for(int j=0;j<f[0].size();j++){
				rui[i][j]+=rui[i-1][j];
			}
		}
		flag = true;
	}
	int get(int a,int b,int c,int d){
		assert(a>=0&&a<f.size());
		assert(b>=0&&b<f[0].size());
		assert(c>=0&&c<f.size());
		assert(d>=0&&d<f[0].size());
		assert(a<=c&&b<=d);
		assert(flag);
		int res = rui[c][d];
		if(a>0)res -= rui[a-1][d];
		if(b>0)res -= rui[c][b-1];
		if(a>0&&b>0)res += rui[a-1][b-1];
		return res;
	}
};
int main(){
	return 0;
}
