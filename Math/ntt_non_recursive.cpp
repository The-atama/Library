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
#define INF 2000000000             // 2e9
#define LLINF 100000000000000000ll // 1e17
#define fi first
#define sec second
#define all(x) (x).begin(), (x).end()
#define sq(x) ((x) * (x))
#define dmp(x) cerr << #x << ": " << x << endl;

template <class T> void chmin(T &a, const T &b) {
  if (a > b)
    a = b;
}
template <class T> void chmax(T &a, const T &b) {
  if (a < b)
    a = b;
}

template <class T> using MaxHeap = priority_queue<T>;
template <class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
template <class T> vector<T> vect(int len, T elem) {
  return vector<T>(len, elem);
}

template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  os << p.fi << ',' << p.sec;
  return os;
}
template <class T, class U> istream &operator>>(istream &is, pair<T, U> &p) {
  is >> p.fi >> p.sec;
  return is;
}
template <class T> ostream &operator<<(ostream &os, const vector<T> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    os << vec[i];
    if (i + 1 < vec.size())
      os << ' ';
  }
  return os;
}
template <class T> istream &operator>>(istream &is, vector<T> &vec) {
  for (int i = 0; i < vec.size(); i++)
    is >> vec[i];
  return is;
}
void fastio() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  cout << fixed << setprecision(20);
}

namespace Math {
template <int MOD> // if inv is needed, this shold be prime.
struct ModInt {
  ll val;
  ModInt() : val(0ll) {}
  ModInt(const ll &v) : val(((v % MOD) + MOD) % MOD) {}
  bool operator==(const ModInt &x) const { return val == x.val; }
  bool operator!=(const ModInt &x) const { return !(*this == x); }
  bool operator<(const ModInt &x) const { return val < x.val; }
  bool operator>(const ModInt &x) const { return val > x.val; }
  bool operator>=(const ModInt &x) const { return !(*this < x); }
  bool operator<=(const ModInt &x) const { return !(*this > x); }
  ModInt operator-() const { return ModInt(MOD - val); }
  ModInt inv() const { return this->pow(MOD - 2); }
  ModInt &operator+=(const ModInt &x) {
    if ((val += x.val) >= MOD)
      val -= MOD;
    return *this;
  }
  ModInt &operator-=(const ModInt &x) {
    if ((val += MOD - x.val) >= MOD)
      val -= MOD;
    return *this;
  }
  ModInt &operator*=(const ModInt &x) {
    (val *= x.val) %= MOD;
    return *this;
  }
  ModInt &operator/=(const ModInt &x) { return *this *= x.inv(); };
  ModInt operator+(const ModInt &x) const { return ModInt(*this) += x; }
  ModInt operator-(const ModInt &x) const { return ModInt(*this) -= x; }
  ModInt operator*(const ModInt &x) const { return ModInt(*this) *= x; }
  ModInt operator/(const ModInt &x) const { return ModInt(*this) /= x; }
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
  ModInt pow(ll x) const {
    auto res = ModInt(1ll);
    auto b = *this;
    while (x) {
      if (x & 1)
        res *= b;
      x >>= 1;
      b *= b;
    }
    return res;
  }
};

template <int MOD> ModInt<MOD> pow(ModInt<MOD> a, ll x) {
  ModInt<MOD> res = ModInt<MOD>(1ll);
  while (x) {
    if (x & 1)
      res *= a;
    x >>= 1;
    a *= a;
  }
  return res;
}

// constexpr int MOD = 1e9+7;
constexpr int MOD = 998244353;
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
  for (int i = 1; i <= SIZE; i++)
    fac[i] = fac[i - 1] * mint(i);
  for (int i = 2; i <= SIZE; i++)
    inv[i] = mint(0ll) - mint(MOD / i) * inv[MOD % i];
  for (int i = 1; i <= SIZE; i++)
    facinv[i] = facinv[i - 1] * inv[i];
  return;
}
template <class T> int digit(T x) {
  int res = 0;
  while (x) {
    x /= T(10);
    res++;
  }
  return res;
}
template <class T> int digit_sum(T x) {
  int res = 0;
  while (x) {
    res += x % 10;
    x /= 10;
  }
  return res;
}
template <class T> T gcd(T x, T y) {
  if (y == T(0))
    return x;
  else
    return gcd(y, x % y);
}
} // namespace Math

using namespace Math;

// Number Theoretical Transform ( require ModInt )
template <ll MOD, ll primitive> class NTT {
public:
  using mint = ModInt<MOD>;
  vector<mint> zetas;
  NTT() {
    ll e = MOD - 1;
    mint root = primitive;
    while (!(e & 1)) {
      zetas.push_back(root.pow(e));
      e >>= 1;
    }
  }

  ll get_MOD() const { return MOD; }

  // swap elements of v (bit-reversal index)
  // http://www.staff.science.uu.nl/~bisse101/Book/PSC/psc3_3.pdf
  template <class T> void bitrev(vector<T> &v) const {
    int n = v.size();
    for (int i = 0; i < n; i++) {
      int tmp = i, j = 0;
      for (int k = 0; (1 << k) < n; k++) {
        int b = (tmp & 1);
        tmp >>= 1;
        j <<= 1;
        j |= b;
      }
      if (i < j) {
        swap(v[i], v[j]);
      }
    }
  }
  // Butter-fly operation
  // easy to understand picture :
  // https://www.onosokki.co.jp/HP-WK/eMM_back/emm140.pdf page 3
  void dft_core(vector<mint> &f, int sgn) const {
    if (f.size() == 1)
      return;
    int l = 1;
    int k = 1 << l;
    int n = f.size();
    while (k <= n) {
      mint zeta = zetas[l];
      if (sgn == -1)
        zeta = zeta.inv();
      for (int r = 0; r < n / k; r++) {
        mint powzeta = 1;
        for (int j = 0; j < k / 2; j++) {
          int b = r * k + j;
          mint t = powzeta * f[b + k / 2];
          f[b + k / 2] = f[b] - t;
          f[b] = f[b] + t;
          powzeta *= zeta;
        }
      }
      l++;
      k <<= 1;
    }
    return;
  }
  void dft(vector<mint> &f, int sgn = 1) const {
    bitrev(f);
    dft_core(f, sgn);
  }
  void idft(vector<mint> &f) const {
    dft(f, -1);
    int n = f.size();
    mint ninv = mint(n).inv();
    for (int i = 0; i < n; i++)
      f[i] *= ninv;
    return;
  }
  vector<mint> mult(vector<mint> A, vector<mint> B) const {
    int n = 1;
    while (n < A.size() + B.size() + 1)
      n <<= 1;
    A.resize(n, mint(0));
    B.resize(n, mint(0));
    dft(A);
    dft(B);
    vector<mint> C;
    for (int i = 0; i < n; i++)
      C.pb(A[i] * B[i]);
    idft(C);
    return C;
  }
};

NTT<998244353ll, 3ll> ntt;

void ATC001_C() {
  int N;
  cin >> N;
  vector<mint> a(N + 1), b(N + 1);
  for (int i = 1; i <= N; i++) {
    cin >> a[i] >> b[i];
  }
  auto c = ntt.mult(a, b);
  for (int i = 1; i <= 2 * N; i++) {
    cout << c[i] << "\n";
  }
  return;
}
int main() {
  ATC001_C();
  return 0;
}
