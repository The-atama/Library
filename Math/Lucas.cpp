// Verified: https://yukicoder.me/submissions/716034

template <class T>
struct Lucas {
  vector<vector<T>> comb;
  T p;
  Lucas(T p) : p(p) { init(p); }
  void init(T p) {
    comb.assign(p, vector<T>(p));
    comb[0][0] = 1;
    for (int i = 1; i < p; i++) {
      comb[i][0] = 1;
      for (int j = i; j > 0; j--) {
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % p;
      }
    }
  }
  T nCk(T n, T k) {
    T ret = 1;
    while (n > 0) {
      T ni = n % p;
      T ki = k % p;
      ret *= comb[ni][ki];
      ret %= p;
      n /= p;
      k /= p;
    }
    return ret;
  }
};
