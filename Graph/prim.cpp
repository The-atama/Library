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
struct edge{int to,cost;};
vector<edge> g[10002];
int mincost[10002];
bool used[10002];
int V,E;
int prim()
{
	for(int i=0;i<10002;i++)
	{
		mincost[i]=INF;
		used[i]=false;
	}
	mincost[0]=0;
	int res=0;
	priority_queue<P,vector<P>,greater<P> > q;
	q.push(P(0,0));
	while(!q.empty())
	{
		P a=q.top();
		q.pop();
		if(used[a.sec])continue;
		used[a.sec]=true;
		res+=mincost[a.sec];
		for(int i=0;i<g[a.sec].size();i++)
		{
			edge e=g[a.sec][i];
			if(used[e.to])continue;
			if(mincost[e.to]>e.cost)
			{
				mincost[e.to]=e.cost;
				q.push(P(mincost[e.to],e.to));
			}
		}
	}
	return res;
}
int main()
{
	cin >> V >> E;
	for(int i=0;i<E;i++)
	{
		int a,b,s;
		cin >> a >> b >> s;
		edge in;
		in.to=a;in.cost=s;
		g[b].pb(in);
		in.to=b;
		g[a].pb(in);
	}
	cout << prim() << endl;
	return 0;
}
