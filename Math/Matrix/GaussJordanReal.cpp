#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> P;
typedef vector<int> vi;
typedef vector<ll> vll;
// #define int long long
#define pb push_back
#define mp make_pair
#define eps 1e-4
#define INF 2000000000              // 2e9
#define LLINF 2000000000000000000ll // 2e18 (llmax:9e18)
#define fi first
#define sec second
#define all(x) (x).begin(), (x).end()
#define sq(x) ((x) * (x))
#define dmp(x) cerr << #x << ": " << x << endl;

// N変数連立方程式(Ax=bの形)を解く
//
// 引数のAは拡大係数行列. (Ax=bでAとbをそのまま並べてつなげたもの)
// すなわち
// A[i][0] * x_0 + A[i][1] * x_1 + ... A[i][n - 1] * x_{n-1} = A[i][n]
// (0 <= i < n)
//
//
// 関数が終わったときにAの左側は単位行列になる
// Note: 誤差に注意
//
// Verify:
// https://onlinejudge.u-aizu.ac.jp/solutions/problem/1328/review/4927454/okuraofvegetable/C++17
// https://onlinejudge.u-aizu.ac.jp/solutions/problem/2171/review/6045411/okuraofvegetable/C++17

vector<double> solve_equation(vector<vector<double>> &A) {
  assert(A[0].size() == A.size() + 1);
  for (int i = 0; i < A.size(); i++) {
    if (abs(A[i][i]) < eps) {
      for (int j = i + 1; j < A.size(); j++) {
        if (abs(A[j][i]) > eps) {
          swap(A[i], A[j]);
          break;
        }
      }
    }
    double r = A[i][i];
    for (int j = i; j <= A.size(); j++) { A[i][j] /= r; }
    for (int j = i + 1; j < A.size(); j++) {
      double s = A[j][i];
      for (int k = i; k <= A.size(); k++) { A[j][k] -= A[i][k] * s; }
    }
  }
  for (int i = A.size() - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      double r = A[j][i];
      for (int k = i; k <= A.size(); k++) { A[j][k] -= A[i][k] * r; }
    }
  }
  vector<double> sol;
  for (int i = 0; i < A.size(); i++) sol.push_back(A[i][A.size()]);
  return sol;
}

double eval(const vector<double> &coeff, double x) {
  double res = 0.0;
  for (int i = 0; i < coeff.size(); i++) { res += std::pow(x, i) * coeff[i]; }
  return res;
}

bool solve() {
  int d;
  cin >> d;
  if (d == 0) return false;
  vector<double> xs(d + 3);
  cin >> xs;
  vector<vector<double>> A(d + 1);
  for (int i = 0; i + 1 < xs.size(); i++) {
    int row = 0;
    for (int j = 0; j < xs.size(); j++) {
      if (j == i || j == i + 1) continue;
      A[row].clear();
      for (int k = 0; k <= d; k++) A[row].push_back(std::pow(j, k));
      A[row].push_back(xs[j]);
      row++;
    }

    auto sol = solve_equation(A);

    double y1 = eval(sol, i);
    double y2 = eval(sol, i + 1);

    bool f1 = false, f2 = false;
    if (abs(y1 - xs[i]) < eps) f1 = true;
    if (abs(y2 - xs[i + 1]) < eps) f2 = true;
    assert(!f1 || !f2);
    if (!f1 && !f2) continue;
    if (!f1)
      cout << i << endl;
    else
      cout << i + 1 << endl;
    return true;
  }
  assert(false);
  return true;
}

int main() {
  while (solve()) {}
  return 0;
}
