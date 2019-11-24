#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#define INF 2000000000
const int SIZE=1<<10;
struct segtree
{
	ll seg[SIZE*2];
	ll func(ll a,ll b){return a+b;}
	void update(int k)
	{
		while(k>0)
		{
			k=(k-1)/2;
			seg[k]=func(seg[k*2+1],seg[k*2+2]);
		}
	}
	ll query(int a,int b,int k,int l,int r)
	{
		if(r<=a||b<=l)return 0;
		else if(a<=l&&r<=b)return seg[k];
		else return func(query(a,b,k*2+1,l,(l+r)/2),query(a,b,k*2+2,(l+r)/2,r));
	}
};
segtree Segtree[SIZE*2];
void Update(int kx,int ky,int x)
{
	kx+=SIZE-1;
	ky+=SIZE-1;
	Segtree[kx].seg[ky]=x;
	while(1)
	{
		Segtree[kx].update(ky);
		if(kx==0)break;
		kx=(kx-1)/2;
		Segtree[kx].seg[ky]=Segtree[kx*2+1].seg[ky]+Segtree[kx*2+2].seg[ky];
	}
	return;
}
ll Query(int a,int b,int c,int d,int k,int l,int r)//note:row row column column
{
	if(r<=a||b<=l)return 0;
	else if(a<=l&&r<=b)return Segtree[k].query(c,d,0,0,SIZE);
	else return Query(a,b,c,d,k*2+1,l,(l+r)/2)+Query(a,b,c,d,k*2+2,(l+r)/2,r);
}
int main()
{
	int N,M,Q;
	scanf("%d %d %d",&N,&M,&Q);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			ll x;
			scanf("%lld",&x);
			Update(i,j,x);
		}
	}
	for(int i=0;i<Q;i++)
	{
		int type;
		scanf("%d",&type);
		if(type==1)
		{
			int x,y,a;
			scanf("%d %d %d",&x,&y,&a);
			Update(x,y,a);
		}
		else
		{
			int x1,x2,y1,y2;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			x2++;y2++;
			printf("%lld\n",Query(x1,x2,y1,y2,0,0,SIZE));
		}
	}
	return 0;
}
