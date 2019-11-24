#include <cstdio>
using namespace std;
typedef long long ll;
#define MAX_N 1010
#define MAX_M 1010
template<class T>
struct BIT{
	T bit[MAX_N+10];
	void add(int i,T x){
		i++;
		while(i<=MAX_N){
			bit[i]+=x;
			i+=i&-i;
		}
		return;
	}
	T sum(int i){
		i++;
		T res=0;
		while(i>0){
			res+=bit[i];
			i-=i&-i;
		}
		return res;
	}
};
template<class T>
struct BIT2D{
	BIT<T> bits[MAX_M+10];
	void add(int i,int j,T x){
		i++;
		while(i<=MAX_M){
			bits[i].add(j,x);
			i+=i&-i;
		}
		return;
	}
	T sum(int i,int j){
		i++;
		T res=0;
		while(i>0){
			res+=bits[i].sum(j);
			i-=i&-i;
		}
		return res;
	}
};
int N,M,Q;
BIT2D<ll> bit;
int main(){
	scanf("%d %d %d",&N,&M,&Q);
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			ll x;
			scanf("%lld",&x);
			bit.add(i,j,x);
		}
	}
	for(int i=0;i<Q;i++){
		int type;
		scanf("%d",&type);
		if(type==1){
			int x,y;
			ll a;
			scanf("%d %d %lld",&x,&y,&a);
			ll n=bit.sum(x,y)-bit.sum(x-1,y)-bit.sum(x,y-1)+bit.sum(x-1,y-1);
			a-=n;
			bit.add(x,y,a);
		}else{
			int x1,y1,x2,y2;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			printf("%lld\n",bit.sum(x2,y2)-bit.sum(x2,y1-1)-bit.sum(x1-1,y2)+bit.sum(x1-1,y1-1));
		}
	}
	return 0;
}
