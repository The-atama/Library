#include <bits/stdc++.h>

using namespace std;

// Z[i] : the longest common prefix of S and S[i:]
struct Zalgorithm {
  string s;
  vector<int> Z;
  explicit Zalgorithm(string s) : s(s) {
    Z.resize(s.size() + 1);
    Z[0] = s.size();
    int i = 1, j = 0;
    while (i < s.size()) {
      while (i + j < s.size() && s[j] == s[i + j]) j++;
      Z[i] = j;
      if (j == 0) {
        i++;
        continue;
      }
      int k = 1;
      while (i + k < s.size() && k + Z[k] < j) {
        Z[i + k] = Z[k];
        ++k;
      }
      i += k;
      j -= k;
    }
  }
  int operator[](int id) const {
    assert(id >= 0 && id < Z.size());
    return Z[id];
  }
};
