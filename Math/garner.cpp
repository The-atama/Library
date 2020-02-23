#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Garner's algorithm
// p[i] must be prime.
// X % p[i] = rem[i]

struct Garner {
  vector<ll> coe;
  vector<ll> p;
  vector<ll> rem;
  ll power_mod(ll x, ll a, ll mod) {
    ll res = 1ll;
    while (a > 0ll) {
      if (a & 1)
        res = (res * x) % mod;
      x = (x * x) % mod;
      a >>= 1;
    }
    return res;
  }
  explicit Garner(vector<ll> &p, vector<ll> &rem) : p(p), rem(rem) {
    assert(p.size() == rem.size());
    coe.resize(p.size());
    vector<vector<ll>> r(p.size(), vector<ll>(p.size()));
    for (int i = 0; i < p.size(); i++) {
      for (int j = 0; j < p.size(); j++) {
        r[i][j] = power_mod(p[i], p[j] - 2ll, p[j]);
      }
    }
    for (int i = 0; i < p.size(); i++) {
      coe[i] = rem[i];
      for (int j = 0; j < i; j++) {
        coe[i] = r[j][i] * (coe[i] - coe[j]);
        coe[i] = ((coe[i] % p[i]) + p[i]) % p[i];
      }
    }
  }
  ll get(ll mod) const {
    ll res = 0ll;
    ll base = 1ll;
    for (int i = 0; i < p.size(); i++) {
      res = (res + base * coe[i]) % mod;
      base = (base * p[i]) % mod;
    }
    return res;
  }
};
signed main() {
  vector<ll> ps = {5, 7, 11}; // 79
  vector<ll> m = {4, 2, 2};
  Garner gn(ps, m);
  cout << gn.get(13) << endl;
  return 0;
}
