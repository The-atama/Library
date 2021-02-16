#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define int ll

#define rng(i, a, b) for (int i = int(a); i < int(b); i++)
#define rep(i, b) rng(i, 0, b)
#define gnr(i, a, b) for (int i = int(b) - 1; i >= int(a); i--)
#define per(i, b) gnr(i, 0, b)
#define pb push_back
#define eb emplace_back
#define a first
#define b second
#define bg begin()
#define ed end()
#define all(x) x.bg, x.ed
#ifdef LOCAL
#define dmp(x) cerr << __LINE__ << " " << #x << " " << x << endl
#else
#define dmp(x) void(0)
#endif

template <class t, class u>
void chmax(t &a, u b) {
  if (a < b) a = b;
}
template <class t, class u>
void chmin(t &a, u b) {
  if (b < a) a = b;
}

template <class t>
using vc = vector<t>;
template <class t>
using vvc = vc<vc<t>>;

using pi = pair<int, int>;
using vi = vc<int>;

template <class t, class u>
ostream &operator<<(ostream &os, const pair<t, u> &p) {
  return os << "{" << p.a << "," << p.b << "}";
}

template <class t>
ostream &operator<<(ostream &os, const vc<t> &v) {
  os << "{";
  for (auto e : v) os << e << ",";
  return os << "}";
}

struct dominator_tree {
  int n;
  vector<vi> g, rG, bct;
  vi idom, semi, us, id, rId, par, mn, anc;
  dominator_tree(int nn)
      : n(nn), g(n), rG(n), bct(n), idom(n, -1), semi(n), us(n), id(n, -1),
        rId(n), par(n, -1), mn(n), anc(n, -1) {
    iota(all(semi), 0);
    iota(all(mn), 0);
  }
  void ae(int a, int b) {
    g[a].pb(b);
    rG[b].pb(a);
  }
  int find(int v) {
    if (anc[v] == -1) return v;
    int a = find(anc[v]);
    if (id[semi[mn[anc[v]]]] < id[semi[mn[v]]]) mn[v] = mn[anc[v]];
    return anc[v] = a;
  }
  void link(int c, int p) { anc[c] = p; }
  void dfs(int v, int p, int &i) {
    if (id[v] != -1) return;
    id[v] = i;
    rId[i++] = v;
    par[v] = p;
    for (int c : g[v]) dfs(c, v, i);
  }
  // return idom or -1 if unreachable from the root
  vi calc(int root) {
    int sz = 0;
    dfs(root, -1, sz);
    for (int i = sz - 1; i > 0; i--) {
      int w = rId[i];
      for (int v : rG[w])
        if (id[v] != -1) {
          find(v);
          if (id[semi[mn[v]]] < id[semi[w]]) semi[w] = semi[mn[v]];
        }
      bct[semi[w]].pb(w);
      for (int v : bct[par[w]]) {
        find(v);
        us[v] = mn[v];
      }
      bct[par[w]].clear();
      link(w, par[w]);
    }
    rng(i, 1, sz) {
      int w = rId[i];
      if (semi[w] == semi[us[w]])
        idom[w] = semi[w];
      else
        idom[w] = idom[us[w]];
    }
    return idom;
  }
};

signed main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  cout << fixed << setprecision(20);

  int n, m, s;
  cin >> n >> m >> s;
  dominator_tree d(n);
  rep(i, m) {
    int a, b;
    cin >> a >> b;
    d.ae(a, b);
  }

  vi p = d.calc(s);
  p[s] = s;
  rep(i, n) cout << p[i] << (i < n - 1 ? " " : "\n");
}
