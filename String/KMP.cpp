#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

template <class T = string>
struct KMP {
  T s;
  vector<int> kmp;
  explicit KMP(T s) : s(s) {
    kmp.resize(s.size() + 1);
    kmp[0] = -1;
    int j = -1;
    for (int i = 0; i < s.size(); i++) {
      while (j >= 0 && s[i] != s[j]) j = kmp[j];
      j++;
      kmp[i + 1] = j;
    }
  }
  int operator[](int id) const {
    assert(id >= 0 && id < kmp.size());
    return kmp[id];
  }
  int get_cycle() { return s.size() - kmp[s.size()]; }
};

namespace PKU2185 {

string get_string_h(const vector<vector<char> > &f, int x) {
  string ret;
  for (int i = 0; i < f[x].size(); i++) ret += f[x][i];
  return ret;
}

string get_string_w(const vector<vector<char> > &f, int y) {
  string ret;
  for (int i = 0; i < f.size(); i++) ret += f[i][y];
  return ret;
}

// we cannot use std::function ! (ha?)
// we have to separate template > brackets! (ha?)
void solve() {
  int r, c;
  scanf("%d %d", &r, &c);
  vector<vector<char> > f(r, vector<char>(c));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) { scanf(" %c", &f[i][j]); }
  }
  int ar, ac;
  {
    vector<string> rs;
    for (int i = 0; i < r; i++) { rs.push_back(get_string_h(f, i)); }
    ar = KMP<vector<string> >(rs).get_cycle();
  }
  {
    vector<string> rc;
    for (int i = 0; i < c; i++) { rc.push_back(get_string_w(f, i)); }
    ac = KMP<vector<string> >(rc).get_cycle();
  }
  printf("%d\n", ar * ac);
  return;
}
}  // namespace PKU2185

int main() {
  PKU2185::solve();
  return 0;
}
