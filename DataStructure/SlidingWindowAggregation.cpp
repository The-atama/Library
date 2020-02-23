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
#define INF 2000000000              // 2e9
#define LLINF 1000000000000000000ll // 1e18
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
} // namespace Math

// Sliding Window Aggregation
// verified https://judge.yosupo.jp/submission/3624
template <class D> struct SWAG {
  stack<pair<D, D>> front, back;
  using DMerger = function<D(D, D)>;
  DMerger dm;
  SWAG(DMerger dm) : dm(dm) {}
  void push(D data) {
    if (back.empty())
      back.push(make_pair(data, data));
    else {
      back.push(make_pair(data, dm(back.top().second, data)));
    }
  }
  void pop() {
    if (front.empty()) {
      while (!back.empty()) {
        auto d = back.top();
        back.pop();
        if (front.empty())
          front.push(make_pair(d.first, d.first));
        else {
          front.push(make_pair(d.first, dm(d.first, front.top().second)));
        }
      }
    }
    front.pop();
  }
  size_t size() { return front.size() + back.size(); }
  D composite_all() {
    assert(front.size() + back.size() > 0);
    if (back.empty())
      return front.top().second;
    if (front.empty())
      return back.top().second;
    return dm(front.top().second, back.top().second);
  }
};

using namespace Math;

struct Data {
  mint a, b;
  Data() {}
  Data(mint a, mint b) : a(a), b(b) {}
};

void QueueOperateAllComposite() {
  int Q;
  cin >> Q;
  auto dm = [](Data f, Data g) { return Data(g.a * f.a, g.a * f.b + g.b); };
  SWAG<Data> swag(dm);
  for (int i = 0; i < Q; i++) {
    int type;
    cin >> type;
    mint a, b, x;
    if (type == 0) {
      cin >> a >> b;
      swag.push(Data(a, b));
    } else if (type == 1) {
      swag.pop();
    } else {
      cin >> x;
      if (swag.size() == 0)
        cout << x << endl;
      else {
        auto func = swag.composite_all();
        cout << func.a * x + func.b << endl;
      }
    }
  }
}

signed main() {
  fastio();
  QueueOperateAllComposite();
  return 0;
}
