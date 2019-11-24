#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
#define INF 2000000000

template <class Monoid>
struct SegmentTree{

	using F = function< Monoid (Monoid,Monoid) >;
	int SIZE;
	vector<Monoid> seg;
	const Monoid id;
	const F f;

	SegmentTree(){}
	SegmentTree(int n,const Monoid& id,const F f):id(id),f(f){
		SIZE = 1;
		while(SIZE<n)SIZE <<= 1;
		seg.assign(2*SIZE,id);
	}

	void update(int k,Monoid x){
		k += SIZE-1;
		seg[k]=x;
		while(k){
			k = (k-1)/2;
			seg[k] = f(seg[k*2+1],seg[k*2+2]);
		}
	}

	Monoid query(int a,int b,int k,int l,int r){
		if(r<=a||b<=l){
			return id;
		}else if(a<=l&&r<=b){
			return seg[k];
		}else{
			Monoid lch = query(a,b,k*2+1,l,(l+r)/2);
			Monoid rch = query(a,b,k*2+2,(l+r)/2,r);
			return f(lch,rch);
		}
	}
};
int main(){
	SegmentTree<int> seg(100,INF,([](int x,int y){return min(x,y);}));
	return 0;
}
