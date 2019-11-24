#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
typedef vector<int> vi;
typedef vector<ll> vll;
#define pb push_back
#define mp make_pair
#define eps 1e-9
#define INF 1000000000
#define LLINF 1000000000000000ll
#define sz(x) ((int)(x).size())
#define fi first
#define sec second
#define all(x) (x).begin(),(x).end()
#define sq(x) ((x)*(x))
#define rep(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define repn(i,a,n) for(int (i)=(a);(i)<(int)(n);(i)++)
#define EQ(a,b) (abs((a)-(b))<eps)
template<class T> void chmin(T& a,const T& b){if(a>b)a=b;}
template<class T> void chmax(T& a,const T& b){if(a<b)a=b;}
template<class T>
void dump(vector<T> &vec){
	for(int i=0;i<vec.size();i++){
		cout << vec[i];
		if(i+1<vec.size())cout << ' ';
		else cout << endl;
	}
	return;
}
struct edge{
	int from,to;
	edge(){}
	edge(int f,int t):from(f),to(t){}
};
struct Tree{
	int V;
	int root;
	vector<int> depth;
	vector<int> par;
	vector<int> subtree_size;
	vector<vector<edge> > G;
	vector<bool> dead; // for centroid decomposition
	vector<int> sz;    // for centroid decomposition
	Tree(){}
	Tree(int v,int r=0){
		V = v;
		root = r;
		G.resize(V);
		depth.resize(V);
		par.resize(V);
		subtree_size.resize(V);
		sz.resize(V,0);
		dead.resize(V,false);
	}
	void add_edge(int u,int v){
		G[u].pb(edge(u,v));
		G[v].pb(edge(v,u));
	}
	int dfs(int v,int p,int d){
		depth[v]=d;
		par[v]=p;
		subtree_size[v]=1;
		for(int i=0;i<G[v].size();i++){
			int u = G[v][i].to;
			if(u==p)continue;
			subtree_size[v]+=dfs(u,v,d+1);
		}
		return subtree_size[v];
	}
	void init(){
		dfs(root,-1,0);
	}

	// following functions are for centroid decomposition
	int subtree_size_dead(int v,int p){
		sz[v] = 1;
		for(int i=0;i<G[v].size();i++){
			int u = G[v][i].to;
			if(u!=p&&!dead[u]){
				sz[v] += subtree_size_dead(u,v);
			}
		}
		return sz[v];
	}
	int centroid_dead(int v,int p,int n){
		for(int i=0;i<G[v].size();i++){
			int u = G[v][i].to;
			if(u!=p&&!dead[u]){
				if(sz[u]>n/2)return centroid_dead(u,v,n);
			}
		}
		return v;
	}
	int centroid_decomposition(int v){
		subtree_size_dead(v,-1);
		int c = centroid_dead(v,-1,sz[v]);
		dead[c] = true;
		int res = 0;
		for(int i=0;i<G[c].size();i++){
			int u = G[c][i].to;
			if(!dead[u]){
				// count something within each subtree alone (without the centroid)
				res = max(res,1+centroid_decomposition(u));
			}
		}
		// count something between subtrees (through centroid)
		dead[c] = false;
		return res;
	}
};
int N;
int main(){
	cin >> N;
	Tree G(N);
	for(int i=0;i<N-1;i++){
		int x,y;
		cin >> x >> y;
		x--;y--;
		G.add_edge(x,y);
	}
	cout << G.centroid_decomposition(0) << endl;
	return 0;
}
