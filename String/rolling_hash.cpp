#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> P;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
// #define int long long
#define pb push_back
#define mp make_pair
#define eps 1e-9
#define INF 2000000000
#define LLINF 10000000000000ll
#define fi first
#define sec second
#define all(x) (x).begin(), (x).end()
#define sq(x) ((x) * (x))
#define dmp(x) cerr << #x << ": " << x << endl;
template <class T>
void chmin(T &a, const T &b) {
  if (a > b) a = b;
}
template <class T>
void chmax(T &a, const T &b) {
  if (a < b) a = b;
}
template <class T>
using MaxHeap = priority_queue<T>;
template <class T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;
template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  os << p.fi << ',' << p.sec;
  return os;
}
template <class T, class U>
istream &operator>>(istream &is, pair<T, U> &p) {
  is >> p.fi >> p.sec;
  return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    os << vec[i];
    if (i + 1 < vec.size()) os << ' ';
  }
  return os;
}
template <class T>
istream &operator>>(istream &is, vector<T> &vec) {
  for (int i = 0; i < vec.size(); i++) is >> vec[i];
  return is;
}
void fastio() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  cout << fixed << setprecision(20);
}

namespace Math {
template <int MOD>  // if inv is needed, this shold be prime.
struct ModInt {
  ll val;
  ModInt() : val(0ll) {}
  ModInt(const ll &v) : val(((v % MOD) + MOD) % MOD) {}
  ModInt pow(ModInt a, ll x) {
    ModInt res = ModInt(1ll);
    while (x) {
      if (x & 1) res *= a;
      x >>= 1;
      a = a * a;
    }
    return res;
  }
  bool operator==(const ModInt &x) const { return val == x.val; }
  bool operator!=(const ModInt &x) const { return !(*this == x); }
  bool operator<(const ModInt &x) const { return val < x.val; }
  bool operator>(const ModInt &x) const { return val > x.val; }
  bool operator>=(const ModInt &x) const { return !(*this < x); }
  bool operator<=(const ModInt &x) const { return !(*this > x); }
  ModInt &operator+=(const ModInt &x) {
    if ((val += x.val) >= MOD) val -= MOD;
    return *this;
  }
  ModInt &operator-=(const ModInt &x) {
    if ((val += MOD - x.val) >= MOD) val -= MOD;
    return *this;
  }
  ModInt &operator*=(const ModInt &x) {
    (val *= x.val) %= MOD;
    return *this;
  }
  ModInt operator+(const ModInt &x) const { return ModInt(*this) += x; }
  ModInt operator-(const ModInt &x) const { return ModInt(*this) -= x; }
  ModInt operator*(const ModInt &x) const { return ModInt(*this) *= x; }
  friend istream &operator>>(istream &i, ModInt &x) {
    ll v;
    i >> v;
    x = v;
    return i;
  }
  friend ostream &operator<<(ostream &o, const ModInt &x) {
    o << x.val;
    return o;
  }
};
constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;
vector<mint> inv, fac, facinv;
// notice: 0C0 = 1
ModInt<MOD> nCr(int n, int r) {
  assert(!(n < r));
  assert(!(n < 0 || r < 0));
  return fac[n] * facinv[r] * facinv[n - r];
}
void init(int SIZE) {
  fac.resize(SIZE + 1);
  inv.resize(SIZE + 1);
  facinv.resize(SIZE + 1);
  fac[0] = inv[1] = facinv[0] = mint(1ll);
  for (int i = 1; i <= SIZE; i++) fac[i] = fac[i - 1] * mint(i);
  for (int i = 2; i <= SIZE; i++)
    inv[i] = mint(0ll) - mint(MOD / i) * inv[MOD % i];
  for (int i = 1; i <= SIZE; i++) facinv[i] = facinv[i - 1] * inv[i];
  return;
}
}  // namespace Math

// verified https://atcoder.jp/contests/abc150/submissions/9431876
// hash[i] = s[0]*B^(i-1)+...+s[i-1]
template <class T, int MOD>
struct RollingHash {
  using Hash = Math::ModInt<MOD>;
  vector<Hash> hash;  // hash[i] is hash of s[0,i)
  vector<Hash> powB;
  const Hash B = Hash(10007);
  T s;
  explicit RollingHash(T s) : s(s) {
    hash.assign(s.size() + 1, Hash(0));
    powB.assign(s.size() + 1, Hash(0));
    powB[0] = Hash(1);
    for (int i = 0; i < s.size(); i++) {
      powB[i + 1] = powB[i] * B;
      hash[i + 1] = hash[i] * B + Hash(s[i]);
    }
  }
  Hash get(int l, int r) {  // [l,r)
    assert(l < r);
    return hash[r] - hash[l] * powB[r - l];
  }
  Hash substr(int l, int len) {  // [l,l+len)
    return get(l, l + len);
  }
  // hash of s+t , length of t is len, powlen = powB[len]
  Hash concat(Hash t, Hash powlen) { return hash[s.size()] * powlen + t; }
};

signed main() {
  fastio();
  int N;
  cin >> N;
  vector<int> a(N), b(N);
  cin >> a;
  cin >> b;
  vector<int> c(2 * N), d(N);
  for (int i = 0; i < N; i++) {
    c[i + N] = c[i] = (a[i] ^ a[(i + 1) % N]);
    d[i] = (b[i] ^ b[(i + 1) % N]);
  }
  const int MOD = 1e9 + 7;
  RollingHash<vector<int>, MOD> rc(c), rd(d);
  for (int i = 0; i < N; i++) {
    if (rc.get(i, i + N) == rd.get(0, N)) {
      cout << i << ' ' << (a[i] ^ b[0]) << endl;
    }
  }
  return 0;
}
