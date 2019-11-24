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
const int MAX_V=100100;
struct edge
{
	int to,cap,rev;
	edge(int to,int cap,int rev):to(to),cap(cap),rev(rev){}
};
vector<edge> G[MAX_V];
bool used[MAX_V];
void add_edge(int from,int to,int cap)
{
	G[from].pb(edge(to,cap,G[to].size()));
	G[to].pb(edge(from,0,G[from].size()-1));
}
int dfs(int v,int t,int f)
{
	if(v==t)return f;
	used[v]=true;
	for(int i=0;i<G[v].size();i++)
	{
		edge &e=G[v][i];
		if(!used[e.to]&&e.cap>0)
		{
			int d=dfs(e.to,t,min(f,e.cap));
			if(d>0)
			{
				e.cap-=d;
				G[e.to][e.rev].cap+=d;
				return d;
			}
		}
	}
	return 0;
}
int max_flow(int s,int t)
{
	int flow=0;
	for(;;)
	{
		memset(used,0,sizeof(used));
		int f=dfs(s,t,INF);
		if(f==0)return flow;
		flow+=f;
	}
}
//dfs wo tukau toki ha memset wo wasureruna!!!!
int main()
{
	int N,M,S,T;
	scanf("%d",&M,&N);
	for(int i=0;i<M;i++)
	{
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		add_edge(a,b,c);
	}
	//scanf("%d %d",&S,&T);
	S=1;T=N;
	printf("%d\n",max_flow(S,T));
	return 0;
}
