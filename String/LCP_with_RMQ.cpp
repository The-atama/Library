// Verified:
// https://onlinejudge.u-aizu.ac.jp/solutions/problem/2711/review/6052124/okuraofvegetable/C++17

struct SuffixArray {
  string s;
  vector<int> sa;
  vector<int> rank;
  vector<int> lcp;
  explicit SuffixArray(string s) : s(s) {
    int n = s.size();
    sa.resize(n + 1);
    rank.resize(n + 1);
    vector<int> tmp(n + 1);
    for (int i = 0; i <= n; i++) {
      rank[i] = (i < n) ? s[i] : -1;
      sa[i] = i;
    }
    for (int k = 1; k <= n; k *= 2) {
      auto compare_sa = [&](const int &i, const int &j) {
        if (rank[i] != rank[j])
          return rank[i] < rank[j];
        else {
          int ri = (i + k <= s.size()) ? rank[i + k] : -1;
          int rj = (j + k <= s.size()) ? rank[j + k] : -1;
          return ri < rj;
        }
      };
      sort(sa.begin(), sa.end(), compare_sa);
      tmp[sa[0]] = 0;
      for (int i = 1; i <= n; i++)
        tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
      for (int i = 0; i <= n; i++) rank[i] = tmp[i];
    }
  }
  size_t size() const { return s.size(); }
  int operator[](int id) const { return sa[id]; }
  bool contain(string t) {
    int l = 0, r = s.size() + 1;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (s.compare(sa[mid], t.size(), t) < 0) {
        l = mid;
      } else {
        r = mid;
      }
    }
    return s.compare(sa[r], t.size(), t) == 0;
  }
};

struct LongestCommonPrefix {
  const SuffixArray &sa;
  vector<int> lcp, rank;
  explicit LongestCommonPrefix(const SuffixArray &sa) : sa(sa) {
    int n = sa.size();
    lcp.resize(sa.size() + 1);
    rank.resize(sa.size() + 1);
    for (int i = 0; i <= sa.size(); i++) { rank[sa[i]] = i; }
    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < sa.size(); i++) {
      int j = sa[rank[i] - 1];
      if (h > 0) h--;
      for (; i + h < n && j + h < n; h++)
        if (sa.s[i + h] != sa.s[j + h]) break;
      lcp[rank[i] - 1] = h;
    }
  }
  int operator[](int id) const {
    assert(id >= 0 && id < lcp.size());
    return lcp[id];
  }
};

template <class D>
struct SegmentTree {
  using DMerger = function<D(D, D)>;
  int length;
  vector<D> seg;
  const DMerger dm;
  const D d_unit;

  SegmentTree() {}
  SegmentTree(int n, const DMerger dm, const D &d_unit)
      : dm(dm), d_unit(d_unit) {
    length = 1;
    while (length < n) length <<= 1;
    seg.assign(2 * length, d_unit);
  }
  SegmentTree(vector<D> vec, const DMerger dm, const D &d_unit)
      : dm(dm), d_unit(d_unit) {
    length = 1;
    while (length < vec.size()) length <<= 1;
    seg.assign(2 * length, d_unit);
    for (int i = 0; i < vec.size(); i++) seg[length - 1 + i] = vec[i];
    for (int i = length - 2; i >= 0; i--)
      seg[i] = dm(seg[i * 2 + 1], seg[i * 2 + 2]);
  }

  void update(int k, D x) {
    k += length - 1;
    seg[k] = x;
    while (k) {
      k = (k - 1) / 2;
      seg[k] = dm(seg[k * 2 + 1], seg[k * 2 + 2]);
    }
  }

  D query(int a, int b, int k, int l, int r) const {
    if (r <= a || b <= l) {
      return d_unit;
    } else if (a <= l && r <= b) {
      return seg[k];
    } else {
      D lch = query(a, b, k * 2 + 1, l, (l + r) / 2);
      D rch = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return dm(lch, rch);
    }
  }
  D query(int a, int b) const { return query(a, b, 0, 0, length); }
  D get_point(int x) const { return seg[length - 1 + x]; }
};

struct RMQFromLCP {
  const LongestCommonPrefix &lcp;
  SegmentTree<int> seg;
  explicit RMQFromLCP(const LongestCommonPrefix &lcp)
      : lcp(lcp), seg(
                      lcp.lcp, [](int a, int b) { return std::min(a, b); },
                      std::numeric_limits<int>::max()) {}
  int getLongestCommonStringFrom(int s, int t) const {
    int L = std::min(lcp.rank[s], lcp.rank[t]);
    int R = std::max(lcp.rank[s], lcp.rank[t]);
    return seg.query(L, R);
  }
};
