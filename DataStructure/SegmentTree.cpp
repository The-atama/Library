#include <bits/stdc++.h>

using namespace std;

template <class D>
struct SegmentTree {
  using DMerger = function<D(D, D)>;
  int length;
  vector<D> seg;
  const D d_unit;
  const DMerger dm;

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

int main() {
#define INF 2000000000
  SegmentTree<int> seg(
      100, [](int x, int y) { return min(x, y); }, INF);
  return 0;
}
