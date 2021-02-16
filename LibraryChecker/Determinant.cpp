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
T determinant(vector<vector<T>> a) {
  T det = 1;
  for (int j = 0, r = 0, n = a.size(); j < n; ++j, ++r) {
    for (int i = r + 1; i < n; ++i)
      if (!(a[i][j] == 0)) {
        swap(a[r], a[i]), det = -det;
        break;
      }
    if (a[r][j] == 0) return 0;
    det *= a[r][j];
    T inv = 1 / a[r][j];
    for (auto &&e : a[r]) e *= inv;
    for (int i = 0; i < n; ++i)
      if (i != r and !(a[i][j] == 0))
        for (int k = n; k-- > j;) a[i][k] -= a[r][k] * a[i][j];
  }
  return det;
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
  int n = getint();
  vector<vector<mint>> a(n, vector<mint>(n));
  for (auto &&v : a) { generate(begin(v), end(v), getint<int>); }
  putint(determinant(a).v);
  writechar();
}
