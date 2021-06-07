// Kitamasa method
//
// Verified: https://atcoder.jp/contests/tdpc/submissions/23266163
//
// param: c, k
// a[n] = c[0] * a[0] + c[1] * a[1] + ... + c[n - 1] * a[n - 1]
//
// return: b
// s.t. a[k] = b[0] * a[0] + b[1] * a[1] + ... b[n - 1] * a[n - 1]
//
// To express the k-th term by a linear combination of the first n terms
//
// O(n^2 log k)

template <class T>
vector<T> kth_coefficients(const vector<T> &c, ll k) {
  int n = c.size();
  auto b = vector(n, T(0));
  if (k < n) {
    b[k] = T(1);
    return b;
  }
  if (k == n) return c;
  if ((k & 1) || k < 2 * n) {
    auto prev_b = kth_coefficients(c, k - 1);
    for (int i = 0; i < n; i++) b[i] = c[i] * prev_b[n - 1];
    for (int i = 0; i + 1 < n; i++) b[i + 1] += prev_b[i];
  } else {
    auto prev_bs = vector(n, vector<T>(n));
    prev_bs[0] = kth_coefficients(c, k / 2);
    for (int i = 0; i + 1 < n; i++) {
      for (int j = 0; j < n; j++) prev_bs[i + 1][j] = c[j] * prev_bs[i][n - 1];
      for (int j = 0; j + 1 < n; j++) prev_bs[i + 1][j + 1] += prev_bs[i][j];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) { b[j] += prev_bs[0][i] * prev_bs[i][j]; }
    }
  }
  return b;
}
