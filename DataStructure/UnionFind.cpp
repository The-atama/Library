#include <bits/stdc++.h>

using namespace std;

struct UnionFind {
  vector<int> par, rank, sz;
  UnionFind(int n) {
    par.assign(n, 0);
    rank.assign(n, 0);
    sz.assign(n, 1);
    for (int i = 0; i < n; i++) par[i] = i;
  }
  int find(const int x) { return (par[x] == x) ? x : (par[x] = find(par[x])); }
  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
      par[x] = y;
      sz[y] += sz[x];
    } else {
      par[y] = x;
      sz[x] += sz[y];
      if (rank[x] == rank[y]) rank[x]++;
    }
  }
  bool same(const int x, const int y) { return find(x) == find(y); }
  int size(const int x) { return sz[find(x)]; }
  vector<vector<int>> components() {
    int n = par.size();
    vector<vector<int>> cs;
    vector<int> idx(n, -1);
    for (int i = 0; i < n; i++) {
      if (find(i) != i) continue;
      idx[i] = cs.size();
      cs.emplace_back();
    }
    for (int i = 0; i < n; i++) {
      int id = idx[find(i)];
      cs[id].push_back(i);
    }
    return cs;
  }
};
int main() {
  return 0;
}
