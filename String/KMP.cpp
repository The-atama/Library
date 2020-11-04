#include <bits/stdc++.h>

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

  vector<int> match(const string &t) {
    vector<int> ids;
    int j = 0;
    for (int i = 0; i < t.size(); i++) {
      while (j >= 0 && s[j] != t[i]) j = kmp[j];
      j++;
      // s[0,j)と一致
      if (j >= s.size()) {
        ids.push_back(i - j + 1);
        j = kmp[j];
      }
    }
    return ids;
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
} // namespace PKU2185

int main() {
  // PKU2185::solve();
  string s, t;
  cin >> s >> t;
  KMP<string> kmp(s);
  auto match = kmp.match(t);
  for (int i = 0; i < match.size(); i++) cout << match[i] << endl;
  return 0;
}
