struct HeavyLightDecomposition {
  vector<vector<int>> g;
  int N, root;
  vector<int> par;
  vector<int> depth, chnum;

  vector<int> top;
  vector<int> head;
  vector<int> heavy;
  vector<int> toseg;
  vector<int> chain_len;

  HeavyLightDecomposition(int N) {
    g.resize(N);
    par.resize(N);
    depth.resize(N);
    chnum.resize(N);
    head.resize(N);
    heavy.resize(N);
    toseg.resize(N);
    chain_len.resize(N);
  }

  void add_edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
  }

  struct state {
    int v, p, d;
    bool go;
    state(int v, int p, int d, bool go) : v(v), p(p), d(d), go(go) {}
    state(int v, int p, bool go) : v(v), p(p), go(go) {}
  };

  void init() {
    dfs();
    decompose();
    construct_toseg();
  }

  void dfs() {
    stack<state> st;
    st.push(state(0, -1, 0, true));
    while (!st.empty()) {
      state now = st.top();
      st.pop();
      int v = now.v, p = now.p, d = now.d;
      if (now.go) {
        depth[v] = d;
        par[v] = p;
        st.push(state(v, p, d, false));
        for (int i = 0; i < g[v].size(); i++) {
          if (g[v][i] == p) continue;
          st.push(state(g[v][i], v, d + 1, true));
        }
      } else {
        chnum[v] = 1;
        for (int i = 0; i < g[v].size(); i++) { chnum[v] += chnum[g[v][i]]; }
      }
    }
    return;
  }

  void decompose() {
    stack<state> st;
    st.push(state(0, -1, true));
    while (!st.empty()) {
      state now = st.top();
      st.pop();
      int v = now.v, p = now.p, istop = now.go;
      if (istop) top.push_back(v);
      int hev = -1;
      int val = -1;
      for (int i = 0; i < g[v].size(); i++) {
        if (g[v][i] == p) continue;
        if (val < chnum[g[v][i]]) {
          val = chnum[g[v][i]];
          hev = g[v][i];
        }
      }
      heavy[v] = hev;
      for (int i = 0; i < g[v].size(); i++) {
        if (g[v][i] == p) continue;
        if (g[v][i] == hev)
          st.push(state(g[v][i], v, false));
        else
          st.push(state(g[v][i], v, true));
      }
    }
  }

  void construct_toseg() {
    int id = 0;
    for (int i = 0; i < top.size(); i++) {
      int now = top[i];
      while (1) {
        if (now == -1) break;
        toseg[now] = id++;
        head[now] = top[i];
        now = heavy[now];
        chain_len[top[i]]++;
      }
    }
  }

  int lca(int u, int v) {
    while (head[u] != head[v]) {
      if (depth[head[u]] < depth[head[v]]) swap(u, v);
      u = par[head[u]];
    }
    return (depth[u] < depth[v]) ? u : v;
  }

  template <class Seg, class D>
  void update(Seg &seg, int v, D x) {
    seg.update(toseg[v], x);
  }

  // accumulate from v to the root
  template <class Seg, class D>
  D solve(Seg &seg, int v) {
    D ret = seg.get_point(toseg[v]);
    int now = v;
    while (now != -1) {
      // [head, now]
      ret = seg.dm(ret, seg.query(toseg[head[now]], toseg[now] + 1));
      now = par[head[now]];
    }
    return ret;
  }
};
