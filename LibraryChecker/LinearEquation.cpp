#include <bits/stdc++.h>
using namespace std;

char readchar() {
  static char buf[1 << 15], *ptr = buf, *end = buf;
  if (ptr == end) ptr = buf, end = buf + fread(buf, 1, 1 << 15, stdin);
  return *ptr++;
}
void writechar(char c = 0) {
  static char buf[1 << 15], *ptr = buf;
  if (ptr == end(buf) or c == 0) fwrite(buf, 1, ptr - buf, stdout), ptr = buf;
  *ptr++ = c;
}
template <class Z = int>
Z getint() {
  char c = readchar();
  bool neg = c == '-';
  Z res = neg ? 0 : c - '0';
  while (isdigit(c = readchar())) res = res * 10 + (c - '0');
  return neg ? -res : res;
}
template <class Z>
void putint(Z a, char delim = '\n') {
  if (a < 0) writechar('-'), a = -a;
  int d[40], i = 0;
  do
    d[i++] = a % 10;
  while (a /= 10);
  while (i--) writechar('0' + d[i]);
  writechar(delim);
}
string getstring(char delim = '\n') {
  string res;
  for (char c; (c = readchar()) != delim;) res += c;
  return res;
}
void putstring(string s, char delim = '\n') {
  for (char c : s) writechar(c);
  writechar(delim);
}

template <class T>
int row_reduce(vector<vector<T>> &a, int lim = 1e9) {
  int n = a.size(), m = a[0].size(), rank = 0;
  for (int j = 0; j < min(m, lim); ++j) {
    for (int i = rank + 1; i < n; ++i)
      if (!(a[i][j] == 0)) {
        swap(a[rank], a[i]);
        break;
      }
    if (a[rank][j] == 0) continue;
    T inv = 1 / a[rank][j];
    for (auto &&e : a[rank]) e *= inv;
    for (int i = 0; i < n; ++i)
      if (i != rank and !(a[i][j] == 0))
        for (int k = m; k-- > j;) a[i][k] -= a[rank][k] * a[i][j];
    if (++rank == n) break;
  }
  return rank;
}

template <class T>
vector<vector<T>> solve_linear(vector<vector<T>> a, vector<T> b) {
  int n = a.size(), m = a[0].size();
  for (int i = 0; i < n; ++i) a[i].push_back(b[i]);
  int rank = row_reduce(a, m);
  for (int i = rank; i < n; ++i)
    if (!(a[i][m] == 0)) return {};
  vector<vector<T>> res(1, vector<T>(m));
  vector<int> pivot(m, -1);
  for (int i = 0, j = 0; i < rank; ++i) {
    while (a[i][j] == 0) ++j;
    res[0][j] = a[i][m], pivot[j] = i;
  }
  for (int j = 0; j < m; ++j)
    if (pivot[j] == -1) {
      vector<T> x(m);
      x[j] = -1;
      for (int k = 0; k < j; ++k)
        if (pivot[k] != -1) x[k] = a[pivot[k]][j];
      res.push_back(x);
    }
  return res;
}

template <class T, class Op = multiplies<T>>
T power(T a, long long n, Op op = multiplies<T>(), T e = {1}) {
  assert(n >= 0);
  while (n) {
    if (n & 1) e = op(e, a);
    if (n >>= 1) a = op(a, a);
  }
  return e;
}

template <unsigned M>
struct modular {
  using m = modular;
  unsigned v;
  modular(long long x = 0) : v((x %= M) < 0 ? x + M : x) {}
  m operator-() const { return m() -= *this; }
  m &operator+=(m b) {
    if ((v += b.v) >= M) v -= M;
    return *this;
  }
  m &operator-=(m b) {
    if (v < b.v) v += M;
    v -= b.v;
    return *this;
  }
  m &operator*=(m b) {
    v = (uint64_t)v * b.v % M;
    return *this;
  }
  m &operator/=(m b) { return *this *= power(b, M - 2); }
  friend m operator+(m a, m b) { return a += b; }
  friend m operator-(m a, m b) { return a -= b; }
  friend m operator*(m a, m b) { return a *= b; }
  friend m operator/(m a, m b) { return a /= b; }
  friend bool operator==(m a, m b) { return a.v == b.v; }
  friend string to_string(m a) { return to_string(a.v); }
};

constexpr long long mod = 998244353;
using mint = modular<mod>;

int main() {
  int n = getint(), m = getint();
  vector<vector<mint>> a(n, vector<mint>(m));
  for (auto &&v : a) { generate(begin(v), end(v), getint<int>); }
  vector<mint> b(n);
  generate(begin(b), end(b), getint<int>);
  auto x = solve_linear(a, b);
  // 解空間の次元
  putint((int)x.size() - 1);
  // 解の一つ、解空間の独立な基底
  for (auto &&v : x) {
    for (int i = 0; i < m; ++i) { putint(v[i].v, " \n"[i == m - 1]); }
  }
  writechar();
}
