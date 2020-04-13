#include <bits/stdc++.h>

using namespace std;

// p[i] : minimum divisor of i
// x is prime <=> p[x] == x
vector<int> eratos(int N) {
  vector<int> p(N + 1);
  p[0] = p[1] = 1;
  for (int i = 2; i <= N; i++) p[i] = i;
  for (int i = 2; i * i <= N; i++) {
    if (p[i] != i) continue;
    for (int j = i * 2; j <= N; j += i) {
      if (p[j] == j) p[j] = i;
    }
  }
  return p;
}

int main() {
  auto p = eratos(20);
  for (int i = 0; i < p.size(); i++) { cout << i << ' ' << p[i] << endl; }
  return 0;
}
