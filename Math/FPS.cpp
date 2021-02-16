// Verify: https://atcoder.jp/contests/hhkb2020/submissions/18990520

// Do not cast FPS* to vector*!
// (Resources that this class allocated would not be freeed properly
// because vector's destructor is not virtual method)

template <class T>
struct FormalPowerSeries : public std::vector<T> {
  using std::vector<T>::vector;
  using std::vector<T>::operator=;
  using F = FormalPowerSeries;

  F operator-() const {
    F f(*this);
    for (auto &x : f) x = -x;
    return f;
  }

  F &operator+=(const F &g) {
    int n = this->size();
    int m = g.size();
    this->resize(max(n, m));
    for (int i = 0; i < m; i++) (*this)[i] += g[i];
    return *this;
  }

  F &operator-=(const F &g) {
    int n = this->size();
    int m = g.size();
    this->resize(max(n, m));
    for (int i = 0; i < m; i++) (*this)[i] -= g[i];
    return *this;
  }

  F &operator+=(const T &c) {
    (*this)[0] += c;
    return *this;
  }

  F &operator-=(const T &c) {
    (*this)[0] -= c;
    return *this;
  }

  F &operator*=(const T &c) {
    for (auto &x : *this) x *= c;
    return *this;
  }

  F &operator/=(const T &c) {
    for (auto &x : *this) x /= c;
    return *this;
  }

  // Mulptiplication with sparse polynomial
  // O(NK) where K is the length of g
  F &operator*=(const vector<pair<int, T>> &g) {
#ifdef LOCAL
    assert(!g.empty());
    assert(std::is_sorted(g.begin(), g.end()));
#endif
    this->resize(this->size() + g.back().first);
    int n = this->size();
    for (int i = n - 1; i >= 0; i--) {
      T res(0);
      for (const auto &[d, c] : g) {
        if (i - d < 0) break;
        res += (*this)[i - d] * c;
      }
      (*this)[i] = res;
    }
    return *this;
  }

  F &operator*(const vector<pair<int, T>> &g) { return F(*this) *= g; }

  // Division with sparse polynomial
  // O(NK) where K is the length of g
  pair<F, F> div(const vector<pair<int, T>> &g) {
#ifdef LOCAL
    assert(!g.empty());
    assert(std::is_sorted(g.begin(), g.end()));
#endif
    F f(*this);
    int n = f.size();
    int max_deg = g.back().first;
    T max_deg_coeff = g.back().second;
    F quo(max(1, n - max_deg), T(0));
    for (int i = n - 1; i >= max_deg; i--) {
      T q = f[i] / max_deg_coeff;
      int k = i - max_deg;
      quo[k] = q;
      for (const auto &[d, c] : g) f[d + k] -= c * q;
      f.pop_back();
    }
    return {quo, f};
  }

  F &operator/(const vector<pair<int, T>> &g) const { return div(g).first; }
  F &operator%(const vector<pair<int, T>> &g) const { return div(g).second; }

  F &operator/=(const vector<pair<int, T>> &g) { return *this = div(g).first; }
  F &operator%=(const vector<pair<int, T>> &g) { return *this = div(g).second; }

  T eval(const T &a) const {
    T b(1), res(0);
    for (auto x : *this) {
      res += x * b;
      b *= a;
    }
    return res;
  }

  // Indefinite integral such that F(0) = 0
  F integral() {
    F f(1, T(0));
    for (int i = 0; i < this->size(); i++) {
      f.push_back((*this)[i] / T(i + 1));
    }
    return f;
  }

  T integral(T a, T b) {
    F f = integral();
    return f.eval(b) - f.eval(a);
  }
};

template <class T>
using fps = FormalPowerSeries<T>;
template <class T>
using sfps = vector<pair<int, T>>;
