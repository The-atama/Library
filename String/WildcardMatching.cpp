#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Pattern Matching with don't care
//
// Reference: P.Clifford and R. Clifford
// "Simple Deterministic Wildcard Matching"
// https://www.informatika.bg/resources/StringMatchingWithFFT.pdf
//
// Complexity:
// m : length of text, O(mlogm)
//
// Note: w is a wildcard (which is -1 by default)

#include <atcoder/convolution>
template <class T>
vector<bool> wildcard_matching(const T &s, const T &p, int w = -1) {
  static constexpr int mod = 1811939329;
  using mint = atcoder::static_modint<mod>;

  const int n = s.size();
  const int m = p.size();

#ifdef LOCAL
  assert(1 <= n);
  assert(m <= n);
  const int mx = std::max(*std::max_element(p.begin(), p.end()),
                          *std::max_element(s.begin(), s.end()));
  // maximum squared diff
  assert(ll(mx) * mx * m < mod);
#endif

  vector<mint> diff(n - m + 1, mint(0));

  auto add_term = [&](const auto f, const auto g) {
    vector<mint> x(n), y(m);
    for (int i = 0; i < n; i++) x[i] = f((int)s[i]);
    for (int i = 0; i < m; i++) y[i] = g((int)p[m - 1 - i]);
    const auto z = atcoder::convolution(x, y);
    for (int i = 0; i < n - m + 1; i++) diff[i] += z[m - 1 + i];
  };

  // Calculate sum of (p_i != w) * (t_{i+j} != w) * (p_i - t_{i+j})^2
  add_term([&](const int v) -> ll { return ll(v != w) * v * v; },
           [&](const int v) -> ll { return ll(v != w); });
  add_term([&](const int v) -> ll { return ll(v != w) * (-2) * v; },
           [&](const int v) -> ll { return ll(v != w) * v; });
  add_term([&](const int v) -> ll { return ll(v != w); },
           [&](const int v) -> ll { return ll(v != w) * v * v; });

  // p matches t[j..] <=> diff[j] = 0
  vector<bool> res(n - m + 1);
  for (int i = 0; i < n - m + 1; i++) res[i] = (diff[i].val() == 0);
  return res;
}

void unittest() {
  vector<int> a = {-1, 0, 1, 0};
  vector<int> b = {0, 1};
  dmp(wildcard_matching(a, b));

  string s = "abracadabra";
  string t = "a?a";
  dmp(wildcard_matching(s, t, '?'));
  return;
}
