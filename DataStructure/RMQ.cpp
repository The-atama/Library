#include <algorithm>
using namespace std;
#define INF 2000000000
const int SIZE = 1<<20;
struct RMQ{
	int seg[SIZE*2];
	void update(int k,int x){
		k += SIZE-1;
		seg[k]=x;
		while(k){
			k = (k-1)/2;
			seg[k]=min(seg[k*2+1],seg[k*2+2]);
		}
	}
	int query(int a,int b,int k,int l,int r)
	{
		if(r<=a||b<=l)return INF;
		else if(a<=l&&r<=b)return seg[k];
		else return min(query(a,b,k*2+1,l,(l+r)/2),query(a,b,k*2+2,(l+r)/2,r));
	}
};
