// a_0 < a_1 < ...
template <class T>
int LIS_strict(const vector<T> &vec) {
  auto dp = vect(vec.size() + 1, numeric_limits<T>::max());
  for (int i = 0; i < vec.size(); i++) {
    *upper_bound(all(dp), vec[i]) = vec[i];
  }
  return lower_bound(all(dp), INF) - dp.begin();
}

// a_0 <= a_1 <= ...
template <class T>
int LIS(const vector<T> &vec) {
  auto dp = vect(vec.size() + 1, numeric_limits<T>::max());
  for (int i = 0; i < vec.size(); i++) {
    *lower_bound(all(dp), vec[i]) = vec[i];
  }
  return lower_bound(all(dp), INF) - dp.begin();
}
