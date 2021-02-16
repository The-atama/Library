#include <bits/stdc++.h>

using namespace std;

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define RREP(i, n) for (int i = (int)(n)-1; i >= 0; --i)
#define FOR(i, a, n) for (int i = (a); i < (n); ++i)
#define RFOR(i, a, n) for (int i = (int)(n)-1; i >= (a); --i)

#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()

#define DUMP(x) cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  os << "[";
  REP(i, SZ(v)) {
    if (i) os << ", ";
    os << v[i];
  }
  return os << "]";
}

template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  return os << "(" << p.first << " " << p.second << ")";
}

template <class T, class U>
ostream &operator<<(ostream &os, const map<T, U> &mp) {
  os << "{";
  int a = 0;
  for (const auto &tp : mp) {
    if (a) os << " ", a = 1;
    os << tp;
  }
  return os << "}";
}

template <class T>
bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using P = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vvll = vector<vll>;

const ll MOD = 1e9 + 7;
const int INF = INT_MAX / 2;
const ll LINF = LLONG_MAX / 2;
const ld eps = 1e-9;

/**
 * @brief Z Algorithm O(|s|)
 * @param s: 文字列(or vector)
 * @return A[i]: SとS[i:n] のLCPの長さ
 */
template <typename T>
vector<int> z_algorithm(const T &s) {
  int n = s.size();
  vector<int> A(n);
  A[0] = n;
  int i = 1, j = 0;
  while (i < n) {
    while (i + j < n && s[j] == s[i + j]) ++j;
    A[i] = j;
    if (j == 0) {
      ++i;
      continue;
    }
    int k = 1;
    while (i + k < n && k + A[k] < j) {
      A[i + k] = A[k];
      ++k;
    }
    i += k;
    j -= k;
  }
  return A;
}

/**
 * @brief Run列挙
 * @maintainer habara-k
 * @date 2020/09/19
 * @param[in] l, r, s: 文字列(or vector)sの区間[l, r) におけるRunを列挙
 * @param[out] res: 極大なRun[l, r)に対する最小周期を格納したmap
 * @details Z-Algorithm に依存
 */

template <typename T>
void run_enumerate(int l, int r, const T &s, map<pair<int, int>, int> &res) {
  if (r - l <= 1) return;
  int m = (l + r) >> 1;
  run_enumerate(l, m, s, res);
  run_enumerate(m, r, s, res);

  auto func = [&](bool rev) {
    T t, tl, tr;
    copy(s.begin() + l, s.begin() + r, back_inserter(t));
    if (rev) {
      reverse(t.begin(), t.end());
      m = l + r - m;
    }
    int len = r - l, mid = m - l;
    copy(t.begin(), t.begin() + mid, back_inserter(tl));
    reverse(tl.begin(), tl.end());
    copy(t.begin() + mid, t.end(), back_inserter(tr));
    copy(t.begin(), t.end(), back_inserter(tr));
    auto zl = z_algorithm(tl), zr = z_algorithm(tr);
    zl.push_back(0);
    for (int k = 1; k <= mid; ++k) {
      int li = m - k - zl[k], ri = m + min(r - m, zr[len - k]);
      if (rev) {
        swap(li, ri);
        li = l + r - li;
        ri = l + r - ri;
      }
      if (ri - li < 2 * k) continue;
      if (li > 0 && s[li - 1] == s[li - 1 + k]) continue;
      if (ri < s.size() && s[ri] == s[ri - k]) continue;
      if (res.count({li, ri}))
        res[{li, ri}] = min(res[{li, ri}], k);
      else
        res[{li, ri}] = k;
    }
  };
  func(0);
  func(1);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  cout << fixed << setprecision(10);
  // ifstream in("in.txt");
  // cin.rdbuf(in.rdbuf());

  string s;
  cin >> s;
  int n = s.size();

  map<pair<int, int>, int> res;
  run_enumerate(0, n, s, res);

  cout << res.size() << endl;
  vector<tuple<int, int, int>> ans;
  for (auto tp : res) {
    ans.emplace_back(tp.second, tp.first.first, tp.first.second);
  }
  sort(ALL(ans));
  for (auto &[t, l, r] : ans) { cout << t << ' ' << l << ' ' << r << endl; }

  return 0;
}
