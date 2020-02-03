#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> P;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
// #define int long long
#define pb push_back
#define mp make_pair
#define eps 1e-9
#define INF 1000000000 //1e9
#define LLINF 1000000000000000ll // 1e15
#define fi first
#define sec second
#define all(x) (x).begin(),(x).end()
#define sq(x) ((x)*(x))
#define dmp(x) cerr << #x << ": " << x << endl;

template<class T> void chmin(T& a,const T& b){if(a>b)a=b;}
template<class T> void chmax(T& a,const T& b){if(a<b)a=b;}

template<class T>
ostream& operator << (ostream &os,const vector<T> &vec){
  for(int i=0;i<vec.size();i++){
    os << vec[i];
    if(i+1<vec.size())os << ' ';
  }
  return os;
}

template<class Cost = int>
struct edge{
  int from,to;
  Cost cost;
  edge(){}
  edge(int f,int t,Cost cost):from(f),to(t),cost(cost){}
};

template<class Cost = int>
struct Tree{
  int V;
  int LOG_V;
  int root;
  vector<int> depth;
  vector<vector<int>> dpar;
  vector<int> par;
  vector<int> subtree_size;
  vector<int> centroid;
  vector<Cost> dist;
  vector<vector<edge<Cost>>> G;
  Tree(){}
  Tree(int V,int r=0) : V(V),root(r) {
    G.resize(V);
    depth.resize(V);
    par.resize(V);
    dist.resize(V);
    subtree_size.resize(V);
  }
  void add_edge(int u,int v,Cost c = Cost(0)){
    G[u].pb(edge<Cost>(u,v,c));
    G[v].pb(edge<Cost>(v,u,c));
  }
  int dfs(int v,int p,int d,Cost c){
    depth[v]=d;
    par[v]=p;
    subtree_size[v]=1;
    dist[v] = c;
    bool is_centroid = true;
    for(auto e : G[v]){
      int u = e.to;
      if(u==p)continue;
      subtree_size[v]+=dfs(u,v,d+1,c+e.cost);
      if(subtree_size[u]>V/2)is_centroid=false;
    }
    if(V-subtree_size[v]>V/2)is_centroid=false;
    if(is_centroid)centroid.pb(v);
    return subtree_size[v];
  }
  void dfs(){
    dfs(root,-1,0,Cost(0));
  }

  void construct_dpar(){ LOG_V = 1; while((1<<LOG_V)<=V)LOG_V++;
    dpar.resize(LOG_V);
    for(int i=0;i<LOG_V;i++)dpar[i].resize(V,-1);
    for(int i=0;i<V;i++)dpar[0][i] = par[i];
    for(int i=1;i<LOG_V;i++){
      for(int j=0;j<V;j++){
        if(dpar[i-1][j]==-1)dpar[i][j]=-1;
        else dpar[i][j] = dpar[i-1][dpar[i-1][j]];
      }
    }
    return;
  }
  int kth_parent(int v,int k){
    int res = v;
    for(int i=0;i<LOG_V;i++){
      if(k&(1<<i))res = dpar[i][res];
      if(res==-1)return -1;
    }
    return res;
  }
  void dump_tree(){
    for(int i=0;i<V;i++){
      printf("id: %d, par %d, depth %d\n",i,par[i],depth[i]);
    }
    return;
  }
};

template<class Cost,class Data>
struct rerooting{
  vector<Data> dp_fixed;
  vector<Data> dp_all;
  Tree<Cost> T;
  using Promoter = function<pair<Data,vector<pair<edge<Cost>,Data>>>
                             (vector<pair<edge<Cost>,Data>>,Cost,Data)>;
  Promoter promoter;
  rerooting(Tree<Cost>& T,vector<Data> dp_fixed,Promoter promoter)
    : T(T), dp_fixed(dp_fixed), promoter(promoter) {
    dp_all.resize(dp_fixed.size());
  }
  void reroot(int v,int p,Cost c,Data dpar){
    vector<pair<edge<Cost>,Data>> children;
    for(auto e : T.G[v]){
      if(e.to == p) continue;
      children.push_back(make_pair(e,dp_fixed[e.to]));
    }
    auto ret = promoter(children,c,dpar);
    dp_all[v] = ret.first;
    for(auto& ed : ret.second){
      auto& e = ed.first;
      auto& d = ed.second;
      reroot(e.to,v,e.cost,d);
    }
  }
};

template<class Cost>
Cost diameter(Tree<Cost>& T){
  auto promoter = [](vector<pair<edge<Cost>,Cost>> edgedata,Cost c,Cost d){
    Cost ret = d+c;
    auto next = edgedata;
    vector<Cost> vec;
    for(auto ed : edgedata){
      auto e = ed.first;
      auto d = ed.second;
      vec.push_back(e.cost+d);
      chmax(ret,e.cost+d);
    }
    vector<Cost> lmax = vec,rmax = vec;
    for(int i=1;i<lmax.size();i++)chmax(lmax[i],lmax[i-1]);
    for(int i=(int)rmax.size()-2;i>=0;i--)chmax(rmax[i],rmax[i+1]);
    for(int i=0;i<next.size();i++){
      Cost left = 0;
      Cost right = 0;
      if(i>0)left = lmax[i-1];
      if(i+1<next.size())right  = rmax[i+1];
      next[i].second = max(c+d,max(left,right));
    }
    return make_pair(ret,next);
  };
  vector<Cost> dp(T.G.size());
  function<Cost(Cost,Cost)> dfs = [&](int v,int p){
    Cost ret = 0;
    for(auto e : T.G[v]){
      if(e.to==p)continue;
      dfs(e.to,v);
      chmax(ret,e.cost+dp[e.to]);
    }
    return dp[v]=ret;
  };
  dfs(0,-1);
  // dmp(dp);
  rerooting<Cost,Cost> rr(T,dp,promoter);
  rr.reroot(0,-1,0,0);
  // dmp(rr.dp_all);
  return *max_element(all(rr.dp_all));
}
int main(){
  int N;
  cin >> N;
  Tree<int> G(N);
  for(int i=0;i<N-1;i++){
    int s,t,w;
    cin >> s >> t >> w;
    G.add_edge(s,t,w);
  }
  cout << diameter(G) << endl;
  return 0;
}
