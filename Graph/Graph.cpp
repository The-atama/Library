#include <bits/stdc++.h>
using namespace std;

template<class Cost>
struct edge{
  int from,to
  Cost cost;
  edge(){}
  edge(int from,int to,Cost cost):from(from),to(to),cost(cost){}
};

template<class Cost>
struct Graph{
  int V;
  vector<vector<edge<Cost>>> G;
  Graph(){}
  Graph(int V):V(V){
    G.resize(V);
  }
  void add_edge(int a,int b,Cost cost = Cost(0)){
    G[a].push_back(edge<Cost>(a,b,cost));
  }
  void add_edge_undirect(int a, int b, Cost cost = Cost(0)){
    G[a].push_back(edge<Cost>(a,b,cost));
    G[b].push_back(edge<Cost>(b,a,cost));
  }
  size_t size() const { return G.size(); }
  const vector<edge<Cost>>& operator [] (int id) const {
    return G[id];
  }
};

template<class Graph>
struct SCC{
  Graph G,rG; // Graph and reverse Graph
  vector<bool> used; 
  vector<int> vs;
  vector<int> cmp_id; // component id
  vector<vector<int>> cmp; // components
  explicit SCC(const Graph G):G(G){
    rG = Graph(G.size());
    used.resize(G.size(),false);
    cmp_id.resize(G.size(),-1);
    for(int i=0;i<G.size();i++){
      for(auto e : G[i]){
        rG.add_edge(e.to,e.from,e.cost);
      }
    }
    for(int i=0;i<G.size();i++){
      if(!used[i])dfs(i);
    }
    used.assign(G.size(),false);
    reverse(vs.begin(),vs.end());
    int id = 0;
    for(int i=0;i<vs.size();i++){
      if(!used[vs[i]]){
        cmp.push_back(vector<int>());
        rdfs(vs[i],id++);
      }
    }
  }
  void dfs(int s){
    used[s]=true;
    for(const auto& e : G[s]){
      if(!used[e.to])dfs(e.to);
    }
    vs.push_back(s);
  }
  void rdfs(int s,int k){
    used[s]=true;
    cmp_id[s]=k;
    cmp[k].push_back(s);
    for(const auto& e : rG[s]){
      if(!used[e.to])rdfs(e.to,k);
    }
  }
};

int main(){
  int N,M;
  cin >> N >> M;
  Graph<int> g(N);
  for(int i=0;i<M;i++){
    int a,b;
    cin >> a >> b;
    g.add_edge(a,b);
  }
  SCC<Graph<int>> scc(g);
  cout << scc.cmp.size() << endl;
  for(int i=0;i<scc.cmp.size();i++){
    cout << scc.cmp[i].size();
    for(int j=0;j<scc.cmp[i].size();j++){
      cout << ' ' << scc.cmp[i][j];
    }
    cout << endl;
  }
  return 0;
}
