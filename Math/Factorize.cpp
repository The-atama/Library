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
