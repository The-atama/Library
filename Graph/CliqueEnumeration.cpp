// Enumerate all cliques
//
// Verified: AOJ 2306
// https://onlinejudge.u-aizu.ac.jp/solutions/problem/2306/review/5309943/okuraofvegetable/C++17
//
// Reference: https://www.slideshare.net/wata_orz/ss-12131479
// Complexity: O(n * 2^(sqrt(2m)))

vector<vector<int>> clique_enumeration(const vector<vector<int>> &g) {
  int N = g.size();
  int M = 0;
  vector<int> deg(N, 0);
  for (int i = 0; i < N; i++) {
    deg[i] = g[i].size();
    M += g[i].size();
  }
  int K = (int)(sqrt(M) + 1.0);
  vector<bool> used(N, false);

  auto mat = vector(N, vector(N, false));
  for (int i = 0; i < N; i++) {
    for (int j : g[i]) { mat[i][j] = mat[j][i] = true; }
  }

  auto check = [&](const vector<int> &vs) {
    for (int v : vs) {
      for (int u : vs) {
        if (v == u) continue;
        if (used[v] || used[u]) continue;
        if (!mat[v][u]) return false;
      }
    }
    return true;
  };

  vector<vector<int>> res;

  for (int t = 0; t < N; t++) {
    vector<pair<int, int>> ds;
    for (int i = 0; i < N; i++) {
      if (!used[i]) ds.emplace_back(deg[i], i);
    }
    auto [d, v] = *min_element(all(ds));
    if (d >= K) {
      assert(ds.size() <= K);
      // brute force
      int A = ds.size();
      for (int S = 1; S < (1 << A); S++) {
        vector<int> vs;
        for (int i = 0; i < A; i++) {
          if ((S >> i) & 1) vs.push_back(ds[i].second);
        }
        if (check(vs)) res.push_back(vs);
      }
      break;
    } else {
      // cliques including vertex v
      vector<int> adj;
      for (int u : g[v]) {
        if (!used[u]) adj.push_back(u);
      }
      int A = adj.size();
      for (int S = 0; S < (1 << A); S++) {
        vector<int> vs({v});
        for (int i = 0; i < A; i++) {
          if ((S >> i) & 1) vs.push_back(adj[i]);
        }
        if (check(vs)) res.push_back(vs);
      }

      // erase v
      used[v] = true;
      for (int u : g[v]) deg[u]--;
    }
  }

  return res;
}
