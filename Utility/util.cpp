
namespace Util {
template <class T>
vector<pair<T, int>> runLength(const vector<T>& v) {
  vector<pair<T, int>> res;
  for (int i = 0; i < v.size(); i++) {
    if (res.empty() || res.back().first != v[i])
      res.push_back(make_pair(v[i], 1));
    else
      res.back().second++;
  }
  return res;
}
template <class T>
void compress(vector<T>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}
}  // namespace Util
