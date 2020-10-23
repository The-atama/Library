// verified WUPC 2020 M
// https://onlinejudge.u-aizu.ac.jp/services/review.html#WUPC2020/4832260
// Rerooting
template <typename sum_t, typename key_t>
struct Rerooting {
  struct Edge {
    int to;
    key_t data;
    sum_t dp, acc_dp;
    Edge() {}
    Edge(int to, key_t data, sum_t dp, sum_t acc_dp)
        : to(to), data(data), dp(dp), acc_dp(acc_dp) {}
  };

  using FM = function<sum_t(sum_t, sum_t)>;
  using GM = function<sum_t(sum_t, key_t)>;

  vector<vector<Edge>> G;
  vector<sum_t> &init;
  const FM f;
  const GM g;
  const sum_t ident;
  vector<sum_t> subdp, dp;

  Rerooting(int V, vector<sum_t> &init, const FM f, const GM g,
            const sum_t &ident)
      : G(V), init(init), f(f), g(g), ident(ident), subdp(V, ident),
        dp(V, ident) {}

  void add_edge(int u, int v, const key_t &d) {
    G[u].emplace_back(v, d, ident, ident);
    G[v].emplace_back(u, d, ident, ident);
  }

  void add_edge_bi(int u, int v, const key_t &d, const key_t &e) {
    G[u].emplace_back(v, d, ident, ident);
    G[v].emplace_back(u, e, ident, ident);
  }

  void dfs_sub(int idx, int par) {
    subdp[idx] = init[idx];
    for (auto &e : G[idx]) {
      if (e.to == par) continue;
      dfs_sub(e.to, idx);
      subdp[idx] = f(subdp[idx], g(subdp[e.to], e.data));
    }
  }

  void dfs_all(int idx, int par, const sum_t &top) {
    sum_t acc = ident;
    for (int i = 0; i < (int)G[idx].size(); i++) {
      auto &e = G[idx][i];
      e.acc_dp = acc;
      e.dp = g(par == e.to ? top : subdp[e.to], e.data);
      acc = f(acc, e.dp);
    }
    dp[idx] = f(init[idx], acc);
    sum_t rev_acc = ident;
    for (int i = (int)G[idx].size() - 1; i >= 0; i--) {
      auto &e = G[idx][i];
      if (e.to != par) dfs_all(e.to, idx, f(init[idx], f(e.acc_dp, rev_acc)));
      e.acc_dp = f(e.acc_dp, rev_acc);
      rev_acc = f(rev_acc, e.dp);
    }
  }

  vector<sum_t> build() {
    dfs_sub(0, -1);
    dfs_all(0, -1, ident);
    return dp;
  }
};

// Example of usage

struct Data {
  ll lsum, dp;
  Data() {}
  Data(ll lsum, ll dp) : lsum(lsum), dp(dp) {}
};

void solve() {
  int N;
  cin >> N;
  vector<ll> l(N);
  vector<Data> init(N);
  cin >> l;
  for (int i = 0; i < N; i++) init[i] = Data(l[i], 0ll);
  auto f1 = [](Data a, Data b) { return Data(a.lsum + b.lsum, a.dp + b.dp); };
  auto f2 = [](Data a, int) { return Data(a.lsum, a.lsum + a.dp); };
  Rerooting<Data, int> g(N, init, f1, f2, Data(0ll, 0ll));
  for (int i = 0; i < N - 1; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g.add_edge_bi(a, b, 0, 0);
  }
  for (auto &ans : g.build()) cout << ans.dp << endl;
  return;
}

signed main() {
  solve();
  return 0;
}
