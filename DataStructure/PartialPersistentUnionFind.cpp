#include <bits/stdc++.h>

using namespace std;

// Verify:
// https://atcoder.jp/contests/code-thanks-festival-2017/submissions/18040461
// @component: https://atcoder.jp/contests/nikkei2019-qual/submissions/18551177

struct PartialPersistentUnionFind {
  const int N;
  int last;
  vector<pair<int, int>> par;
  vector<vector<pair<int, int>>> child;
  vector<vector<pair<int, int>>> sz;

  PartialPersistentUnionFind(const int N)
      : N(N), last(numeric_limits<int>::min()), par(N), child(N), sz(N) {
    for (int i = 0; i < N; ++i) {
      par[i] = {numeric_limits<int>::max(), i};
      sz[i].emplace_back(numeric_limits<int>::min(), 1);
    }
  }

  int find(int u, const int t) {
    while (par[u].first <= t) u = par[u].second;
    return u;
  }

  bool unite(int u, int v, const int t) {
    assert(last <= t);
    last = t;
    u = find(u, t), v = find(v, t);
    if (u == v) return false;
    if (sz[u].back().first < sz[v].back().first) swap(u, v);
    par[v] = {t, u};
    child[u].emplace_back(t, v);
    sz[u].emplace_back(t, sz[u].back().second + sz[v].back().second);
    return true;
  }

  bool same(const int u, const int v, const int t) {
    return find(u, t) == find(v, t);
  }

  vector<int> component(int u, const int t) {
    u = find(u, t);
    queue<int> q;
    q.push(u);
    vector<int> comp;
    while (!q.empty()) {
      int v = q.front();
      comp.push_back(v);
      q.pop();
      for (int i = 0; i < child[v].size(); i++) {
        if (child[v][i].first > t) break;
        q.push(child[v][i].second);
      }
    }
    return comp;
  }

  int size(int u, const int t) {
    u = find(u, t);
    int idx = upper_bound(sz[u].begin(), sz[u].end(),
                          make_pair(t, numeric_limits<int>::max())) -
              sz[u].begin();
    return sz[u][idx - 1].second;
  }
};
