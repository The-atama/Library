#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <iostream>
#include <map>
#include <set>
using namespace std;
typedef pair<int,int> P;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
#define pu push
#define pb push_back
#define mp make_pair
#define eps 1e-9
#define INF 2000000000
#define sz(x) ((int)(x).size())
#define fi first
#define sec second
#define SORT(x) sort((x).begin(),(x).end())
#define all(x) (x).begin(),(x).end()
#define rep(i,n) for(int (i)=0;(i)<(n);(i)++)
#define repn(i,a,n) for(int (i)=(a);(i)<(n);(i)++)
#define EQ(a,b) (abs((a)-(b))<eps)
int N;
int H[100100];
int next[100100][20];
const int SIZE = 1<<20;
struct segtree
{
	int seg[SIZE*2];
	segtree(){memset(seg,-1,sizeof(seg));}
	void lazy_evaluate(int k)
	{
		if(k<SIZE-1)
		{
			seg[k*2+1]=seg[k];
			seg[k*2+2]=seg[k];
		}
		seg[k]=-1;
	}
	void set(int a,int b,int k,int l,int r,int v)
	{
		if(a==l&&b==r)
		{
			seg[k]=v;
			return;
		}
		if(seg[k]>-1)lazy_evaluate(k);
		if(b<=(l+r)/2)set(a,b,k*2+1,l,(l+r)/2,v);
		else if(a>=(l+r)/2)set(a,b,k*2+2,(l+r)/2,r,v);
		else
		{
			set(a,(l+r)/2,k*2+1,l,(l+r)/2,v);
			set((l+r)/2,b,k*2+2,(l+r)/2,r,v);
		}
	}
	int get(int x,int k,int l,int r)
	{
		if(r-l==1&&l==x)return seg[k];
		if(seg[k]>-1)lazy_evaluate(k);
		if(x<(l+r)/2)return get(x,k*2+1,l,(l+r)/2);
		else return get(x,k*2+2,(l+r)/2,r);
	}
};
segtree seg;
//stack　で書かないと
int main()
{
	scanf("%d",&N);
	rep(i,N)scanf("%d",&H[i]);
	reverse(H,H+N);
	memset(next,-1,sizeof(next));
	for(int i=N-1;i>=0;i--)
	{
		next[i][0]=seg.get(H[i],0,0,SIZE);
		seg.set(0,H[i]+1,0,0,SIZE,i);
	}
	for(int i=0;i<19;i++)
	{
		rep(j,N)
		{
			if(next[j][i]==-1)next[j][i+1]=-1;
			else next[j][i+1]=next[next[j][i]][i];
		}
	}
	vector<int> ans(N);
	repn(i,1,N)
	{
		int cnt = 0,now=i;
		for(int j=19;j>=0;j--)
		{
			if(next[now][j]!=-1)
			{
				now=next[now][j];
				cnt += 1<<j;
			}
		}
		ans[i-1]=cnt;
	}
	ans[N-1]=-1;
	reverse(all(ans));
	rep(i,N)printf("%d\n",ans[i]+1);
	return 0;
}
