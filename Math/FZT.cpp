// g(S) = sum{ f(T) | T >= S }
template <typename T>
void fzt_upper(vector<T> &f) {
  int n = f.size();
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) { f[j] += f[j | i]; }
    }
  }
}

// g(S) = sum{ f(T) | T <= S }
template <typename T>
void fzt_lower(vector<T> &f) {
  int n = f.size();
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) { f[j | i] += f[j]; }
    }
  }
}

// fzt_upperの逆変換
template <typename T>
void fmt_upper(vector<T> &f) {
  int n = f.size();
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) { f[j] -= f[j | i]; }
    }
  }
}

// fzt_lowerの逆変換
template <typename T>
void fmt_lower(vector<T> &f) {
  int n = f.size();
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) { f[j | i] -= f[j]; }
    }
  }
}

// f(i) = sum { f(j) | i % j == 0}
template <class T>
void zeta_divisor(vector<T> &f) {
  int n = f.size();
  vector<bool> sieve(n, true);
  for (int p = 2; p < n; ++p) {
    if (sieve[p]) {
      for (int k = 1; k * p < n; ++k) {
        sieve[k * p] = false;
        f[k * p] += f[k];
      }
    }
  }
}

// zeta_divisorの逆変換
template <class T>
void mobius_divisor(vector<T> &f) {
  int n = f.size();
  vector<bool> sieve(n, true);
  for (int p = 2; p < n; ++p) {
    if (sieve[p]) {
      for (int k = 1; k * p < n; ++k) {
        sieve[k * p] = false;
        f[k] -= f[k * p];
      }
    }
  }
}
