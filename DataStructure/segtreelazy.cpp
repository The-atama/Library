#include <algorithm>
#define INF 2000000000;
using namespace std;
const int SIZE = 1<<18;
struct segtree
{
	int minimum[SIZE*2],lazy[SIZE*2];
	void lazy_evaluate(int k)
	{
		minimum[k]+=lazy[k];
		if(k<SIZE-1)// k isn't leaf of SegmentTree
		{
			lazy[2*k+1]+=lazy[k];
			lazy[2*k+2]+=lazy[k];
		}
		lazy[k]=0;
	}
	void update(int a,int b,int k,int l,int r,int x)
	{
		lazy_evaluate(k);
		if(r<=a||b<=l)return;
		if(a<=l&&r<=b)
		{
			lazy[k]+=x;
			lazy_evaluate(k);
		}
		else
		{
			update(a,b,k*2+1,l,(l+r)/2,x);
			update(a,b,k*2+2,(l+r)/2,r,x);
			minimum[k] = min(minimum[k*2+1],minimum[k*2+2]);
			return;
		}
	}
	int query(int a,int b,int k,int l,int r)
	{
		lazy_evaluate(k);
		if(r<=a||b<=l)return INF; // min,max henkouji chuui !!!!!!!
		if(a<=l&&r<=b)return minimum[k];
		else
		{
			int lch = query(a,b,k*2+1,l,(l+r)/2);
			int rch = query(a,b,k*2+2,(l+r)/2,r);
			return min(lch,rch);
		}
	}
};
int main(){}
