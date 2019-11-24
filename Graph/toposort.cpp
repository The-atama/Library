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
#define rep(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define repn(i,a,n) for(int (i)=(a);(i)<(int)(n);(i)++)
#define EQ(a,b) (abs((a)-(b))<eps)
vector<int> G[100100];
bool used[100100];
int V,E;
vector<int> topo;
void dfs(int v)
{
	used[v]=true;
	for(int i=0;i<G[v].size();i++)if(!used[G[v][i]])dfs(G[v][i]);
	topo.pb(v);
}
void construct_topo()
{
	memset(used,false,sizeof(used));
	for(int i=0;i<V;i++)if(!used[i])dfs(i);
	reverse(all(topo));
}
int main()
{
	scanf("%d %d",&V,&E);
	for(int i=0;i<E;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		G[a].pb(b);
	}
	construct_topo();
	for(int i=0;i<topo.size();i++)printf("%d\n",topo[i]);
	return 0;
}

