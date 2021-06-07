#include <bits/stdc++.h>

using namespace std;

// D requires operator +,-
template <class D>
struct RangeSum2D {
  vector<vector<D>> f;
  vector<vector<D>> rui;
  bool flag;
  RangeSum2D() { flag = false; }
  RangeSum2D(int H, int W) {
    flag = false;
    f.resize(H);
    for (int i = 0; i < H; i++) f[i].resize(W);
  }
  void set(int x, int y, D v) {
    assert(x < f.size() && y < f[0].size());
    assert(!flag);
    f[x][y] = v;
  }
  void calc() {
    rui = f;
    for (int i = 0; i < f.size(); i++) {
      for (int j = 1; j < f[0].size(); j++) { rui[i][j] += rui[i][j - 1]; }
    }
    for (int i = 1; i < f.size(); i++) {
      for (int j = 0; j < f[0].size(); j++) { rui[i][j] += rui[i - 1][j]; }
    }
    flag = true;
  }
  D get(int a, int b, int c, int d) {
    assert(a >= 0 && a < f.size());
    assert(b >= 0 && b < f[0].size());
    assert(c >= 0 && c < f.size());
    assert(d >= 0 && d < f[0].size());
    assert(a <= c && b <= d);
    assert(flag);
    D res = rui[c][d];
    if (a > 0) res -= rui[a - 1][d];
    if (b > 0) res -= rui[c][b - 1];
    if (a > 0 && b > 0) res += rui[a - 1][b - 1];
    return res;
  }
};
int main() {
  return 0;
}
