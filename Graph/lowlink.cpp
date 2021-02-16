// e(u,v) is bridge <=> ord(u) < lowlink(v)
// vが関節点 <=> ord[u] ≦ lowlink[v]となるvの子が存在する(if v != root)
//           <=> 子が2つ以上 (if v is root)
template <class Graph>
struct LowLink {
  vector<bool> used;
  vector<int> ord, low;
  explicit LowLink(const Graph &g, int root = 0)
      : used(g.size(), false), ord(g.size(), 0), low(g.size(), 0) {
    int k = 0;
    function<void(int, int)> dfs = [&](int v, int p) -> void {
      used[v] = true;
      low[v] = ord[v] = k++;
      for (auto e : g[v]) {
        if (!used[e.to]) {
          dfs(e.to, v);
          low[v] = min(low[v], low[e.to]);
        } else if (e.to != p) {
          low[v] = min(low[v], ord[e.to]);
        }
      }
      return;
    };
    dfs(root, -1);
  }
};
