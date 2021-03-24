#include <bits/stdc++.h>

using namespace std;

template <class D, class O>
struct LazySegmentTree {
  using DMerger = function<D(D, D)>;
  using OMerger = function<O(O, O)>;
  using Applier = function<D(D, O, int)>;

  int length;
  D d_unit;
  O o_unit;

  vector<D> seg;
  vector<O> lazy;

  DMerger dm;
  OMerger om;
  Applier app;

  void lazy_evaluate(int k, int len) {
    if (lazy[k] == o_unit) return;
    if (len > 1) {
      lazy[2 * k + 1] = om(lazy[2 * k + 1], lazy[k]);
      lazy[2 * k + 2] = om(lazy[2 * k + 2], lazy[k]);
    }
    seg[k] = app(seg[k], lazy[k], len);
    lazy[k] = o_unit;
  }
  void update(int a, int b, int k, int l, int r, O x) {
    lazy_evaluate(k, r - l);
    if (r <= a || b <= l)
      return;
    else if (a <= l && r <= b) {
      lazy[k] = om(lazy[k], x);
      lazy_evaluate(k, r - l);
    } else {
      update(a, b, k * 2 + 1, l, (l + r) / 2, x);
      update(a, b, k * 2 + 2, (l + r) / 2, r, x);
      seg[k] = dm(seg[k * 2 + 1], seg[k * 2 + 2]);
    }
  }
  void update(int a, int b, O x) { update(a, b, 0, 0, length, x); }
  D query(int a, int b, int k, int l, int r) {
    lazy_evaluate(k, r - l);
    if (r <= a || b <= l)
      return d_unit;
    else if (a <= l && r <= b)
      return seg[k];
    else {
      D lch = query(a, b, k * 2 + 1, l, (l + r) / 2);
      D rch = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return dm(lch, rch);
    }
  }
  D query(int a, int b) { return query(a, b, 0, 0, length); }
  LazySegmentTree(int n, D d_unit, O o_unit, DMerger dm, OMerger om,
                  Applier app)
      : length(1), d_unit(d_unit), o_unit(o_unit), dm(dm), om(om), app(app) {
    while (length < n) { length <<= 1; }
    seg.assign(length * 2, d_unit);
    lazy.assign(length * 2, o_unit);
  }
  LazySegmentTree(vector<D> vec, D d_unit, O o_unit, DMerger dm, OMerger om,
                  Applier app)
      : length(1), d_unit(d_unit), o_unit(o_unit), dm(dm), om(om), app(app) {
    while (length < vec.size()) { length <<= 1; }
    seg.assign(length * 2, d_unit);
    lazy.assign(length * 2, o_unit);
    for (int i = 0; i < vec.size(); i++) seg[length - 1 + i] = vec[i];
    for (int i = length - 2; i >= 0; i--)
      seg[i] = dm(seg[i * 2 + 1], seg[i * 2 + 2]);
  }
};

// RangeAddRangeSum update : a[l,r) += c
// verified https://atcoder.jp/contests/abc153/submissions/9866001
template <class T>
LazySegmentTree<T, T> RangeAddRangeSum(int size) {
  auto dm = [](T a, T b) { return a + b; };
  auto om = [](T a, T b) { return a + b; };
  auto app = [](T dat, T lz, int len) { return dat + lz * T(len); };
  return LazySegmentTree<T, T>(size, T(0), T(0), dm, om, app);
}

template <class T>
LazySegmentTree<T, T> RangeAddRangeSum(vector<T> vec) {
  auto dm = [](T a, T b) { return a + b; };
  auto om = [](T a, T b) { return a + b; };
  auto app = [](T dat, T lz, int len) { return dat + lz * T(len); };
  return LazySegmentTree<T, T>(vec, T(0), T(0), dm, om, app);
}

// RangeAddRangeMin
// NOT verified yet
LazySegmentTree<ll, ll> RangeAddRangeMin(int size) {
  auto dm = [](ll a, ll b) { return min(a, b); };
  auto om = [](ll a, ll b) { return a + b; };
  auto app = [](ll dat, ll lz, int len) { return dat + lz; };
  return LazySegmentTree<ll, ll>(size, LLINF, 0ll, dm, om, app);
}
LazySegmentTree<ll, ll> RangeAddRangeMin(vector<ll> vec) {
  auto dm = [](ll a, ll b) { return min(a, b); };
  auto om = [](ll a, ll b) { return a + b; };
  auto app = [](ll dat, ll lz, int len) { return dat + lz; };
  return LazySegmentTree<ll, ll>(vec, LLINF, 0ll, dm, om, app);
}

// RangeAffineRangeSum update (l,r,(p,q)) : a[i] = p * a[i] + q { i in [l,r) }
// verified https://judge.yosupo.jp/submission/3354
template <class T>
LazySegmentTree<T, pair<T, T>> RangeAffineRangeSum(int size) {
  using f = pair<T, T>;
  auto dm = [](T a, T b) { return a + b; };
  auto om = [](f a, f b) { return f(b.fi * a.fi, b.fi * a.sec + b.sec); };
  auto app = [](T dat, f lz, int len) { return lz.fi * dat + lz.sec * T(len); };
  return LazySegmentTree<T, f>(size, T(0), f(T(1), T(0)), dm, om, app);
}
template <class T>
LazySegmentTree<T, pair<T, T>> RangeAffineRangeSum(vector<T> vec) {
  using f = pair<T, T>;
  auto dm = [](T a, T b) { return a + b; };
  auto om = [](f a, f b) { return f(b.fi * a.fi, b.fi * a.sec + b.sec); };
  auto app = [](T dat, f lz, int len) { return lz.fi * dat + lz.sec * T(len); };
  return LazySegmentTree<T, f>(vec, T(0), f(T(1), T(0)), dm, om, app);
}

signed main() {
  using ll = long long;
  auto dm = [](ll a, ll b) { return a + b; };
  auto om = [](ll a, ll b) { return a + b; };
  auto app = [](ll dat, ll lz, int len) { return dat + lz * len; };
  LazySegmentTree<ll, ll> seg(100, 0ll, 0ll, dm, om, app);
  return 0;
}
