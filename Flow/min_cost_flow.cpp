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
#define INF 2000000000 //koko wo ijiruna !!!! ryuuryou nadono INF to kondou shiteha ikenaizo
#define sz(x) ((int)(x).size())
#define fi first
#define sec second
#define SORT(x) sort((x).begin(),(x).end())
#define all(x) (x).begin(),(x).end()
#define EQ(a,b) (abs((a)-(b))<EPS)
const int MAX_V=100100;
int V,E;
struct edge
{
	int to,cap,cost,rev;
	edge(int to,int cap,int cost,int rev):to(to),cap(cap),cost(cost),rev(rev){}
};
vector<edge> G[MAX_V];
int h[MAX_V],dist[MAX_V],prevv[MAX_V],preve[MAX_V];
void add_edge(int from,int to,int cap,int cost)
{
	G[from].pb(edge(to,cap,cost,G[to].size()));
	G[to].pb(edge(from,0,-cost,G[from].size()-1));
}
int min_cost_flow(int s,int t,int f)
{
	int res=0;
	fill(h,h+V,0);
	while(f>0)
	{
		priority_queue<P,vector<P>,greater<P> > q;
		fill(dist,dist+V,INF);
		dist[s]=0;
		q.push(mp(0,s));
		while(!q.empty())
		{
			P p=q.top();q.pop();
			int v=p.sec;
			if(dist[v]<p.fi)continue;
			for(int i=0;i<G[v].size();i++)
			{
				edge &e=G[v][i];
				if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to])
				{
					dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
					prevv[e.to]=v;
					preve[e.to]=i;
					q.push(mp(dist[e.to],e.to));
				}
			}
		}
		if(dist[t]==INF)
		{
			return -1;
		}
		for(int v=0;v<V;v++)h[v]+=dist[v];
		int d=f;
		for(int v=t;v!=s;v=prevv[v])
		{
			d=min(d,G[prevv[v]][preve[v]].cap);
		}
		f-=d;
		res+=d*h[t];
		for(int v=t;v!=s;v=prevv[v])
		{
			edge &e=G[prevv[v]][preve[v]];
			e.cap-=d;
			G[v][e.rev].cap+=d;
		}
	}
	return res;
}
int main()
{
	// V ni kanarazu atai wo dainyuu surukoto !!!
	// E ha fuhituyou !
	scanf("%d",&V);
	scanf("%d",&E);
	for(int i=0;i<E;i++)
	{
		int a,b,cap,cost;
		scanf("%d %d %d %d",&a,&b,&cap,&cost);
		add_edge(a,b,cap,cost);
	}
	int S,T,F;
	scanf("%d %d %d",&S,&T,&F);
	printf("%d\n",min_cost_flow(S,T,F));
	return 0;
}
