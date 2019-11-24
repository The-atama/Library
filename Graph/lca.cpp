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
#define MAX_N 100000
#define MAX_LOG_V 20
vector<int> g[MAX_N];
int N,Q,root=0;
int parent[MAX_LOG_V][MAX_N];
int depth[MAX_N];
void dfs(int v,int p,int d){
	depth[v]=d;
	parent[0][v]=p;
	for(int i=0;i<g[v].size();i++){
		if(g[v][i]!=p){
			dfs(g[v][i],v,d+1);
		}
	}
	return;
}
/*
struct state{
	int v,p,d;
	state(int v,int p,int d):v(v),p(p),d(d){};
};
void dfs(){
	stack<state> st;
	st.push(state(0,-1,0));
	while(!st.empty()){
		state now = st.top();
		st.pop();
		int v = now.v,p = now.p,d = now.d;
		depth[v]=d;
		parent[0][v]=p;
		for(int i=0;i<g[v].size();i++){
			edge e = g[v][i];
			if(e.to!=p){
				st.push(state(e.to,v,d+1));
			}
		}
	}
	return;
}*/
void init(){
	dfs(root,-1,0);
	//dfs();
	for(int i=0;i<MAX_LOG_V-1;i++){
		for(int v=0;v<N;v++){
			if(parent[i][v]==-1)parent[i+1][v]=-1;
			else parent[i+1][v]=parent[i][parent[i][v]];
		}
	}
	return;
}
int lca(int u,int v){
	if(depth[u]>depth[v])swap(u,v);
	for(int i=MAX_LOG_V-1;i>=0;i--){
		if(((depth[v]-depth[u])>>i)&1)v=parent[i][v];
	}
	if(u==v)return u;
	for(int i=MAX_LOG_V-1;i>=0;i--){
		if(parent[i][u]!=parent[i][v]){
			u=parent[i][u];
			v=parent[i][v];
		}
	}
	return parent[0][u];
}
int main(){
	cin >> N;
	for(int i=0;i<N;i++){
		int k;
		cin >> k;
		for(int j=0;j<k;j++){
			int c;
			cin >> c;
			g[i].pb(c);
		}
	}
	init();
	cin >> Q;
	for(int i=0;i<Q;i++){
		int u,v;
		cin >> u >> v;
		cout << lca(u,v) << endl;
	}
	return 0;
}
