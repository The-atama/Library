vector<int> Basis(const vector<int> &a) {
  vector<int> bs;
  for (int i = 0; i < a.size(); i++) {
    int x = a[i];
    for (int b : bs) { chmin(x, x ^ b); }
    if (x) bs.push_back(x);
  }
  return bs;
}
