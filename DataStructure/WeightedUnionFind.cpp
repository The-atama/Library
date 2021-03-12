// verified ABC 090 D
// https://atcoder.jp/contests/arc090/submissions/7634267
struct WeightedUnionFind {
  vector<int> par;
  vector<int> rank;
  vector<int> diff;

  WeightedUnionFind(int n) {
    par.resize(n);
    for (int i = 0; i < n; i++) par[i] = i;
    rank.assign(n, 0);
    diff.assign(n, 0);
  }

  int find(int x) {
    if (par[x] == x)
      return x;
    else {
      int r = find(par[x]);
      diff[x] += diff[par[x]];
      return par[x] = r;
    }
  }

  int weight(int x) {
    find(x);
    return diff[x];
  }

  int dist(int x, int y) { // x -> y
    assert(same(x, y));
    return weight(y) - weight(x);
  }

  bool same(int x, int y) { return find(x) == find(y); }

  void unite(int x, int y, int w) { // set diff(x,y) = w
    w += weight(x);
    w -= weight(y);
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
      swap(x, y);
      w = -w;
    }
    if (rank[x] == rank[y]) rank[x]++;
    par[y] = x;
    diff[y] = w;
    return;
  }
};
