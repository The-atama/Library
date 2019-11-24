#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <algorithm>
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
#define EQ(a,b) (abs((a)-(b))<EPS)
struct UnionFind
{
	int par[105];
	int rank[105];
	UnionFind()
	{
		memset(rank,0,sizeof(rank));
		for(int i=0;i<105;i++)par[i]=i;
	}
	int find(int a)
	{
		if(par[a]==a)return a;
		return find(par[a]);
	}
	void unite(int a,int b)
	{
		a=find(a);
		b=find(b);
		if(rank[a]>rank[b])par[b]=a;
		else
		{
			par[a]=b;
			if(rank[a]==rank[b])rank[b]++;
		}
	}
	bool same(int a,int b)
	{
		return find(a)==find(b);
	}
};
struct edge{int from,to,cost;};
vector<edge> all;
int n;
bool comp(const edge& a,const edge& b)
{
	return a.cost < b.cost;
}
int kruskal()
{
	int res=0;
	UnionFind uf;
	sort(all.begin(),all.end(),comp);
	for(int i=0;i<all.size();i++)
	{
		if(!uf.same(all[i].from,all[i].to))
		{
			uf.unite(all[i].from,all[i].to);
			res+=all[i].cost;
		}
	}
	return res;
}
int main()
{
	while(cin >> n)
	{
		all.clear();
		// input edges data
		/*for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				int c;
				scanf("%d",&c);
				edge in;
				in.from=i;in.to=j;in.cost=c;
				all.pb(in);
			}
		}*/
		printf("%d\n",kruskal());
	}
	return 0;
}
