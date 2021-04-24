vector<pair<ll, int>> factorize(ll x) {
  ll tmp = x;
  vector<pair<ll, int>> ret;
  for (ll i = 2ll; i * i <= x; i++) {
    int cnt = 0;
    while (tmp % i == 0ll) {
      tmp /= i;
      cnt++;
    }
    if (cnt > 0) ret.push_back(pair<ll, int>(i, cnt));
  }
  if (tmp != 1ll) ret.push_back(pair<ll, int>(tmp, 1));
  return ret;
}

vector<ll> divisor(const vector<pair<ll, int>> &fs) {
  vector<ll> ds;
  function<void(int, ll)> rec = [&](int n, ll val) {
    if (n == fs.size()) {
      ds.push_back(val);
      return;
    }
    for (int i = 0; i <= fs[n].second; i++) {
      rec(n + 1, val);
      val *= fs[n].first;
    }
  };
  rec(0, 1ll);
  return ds;
}
