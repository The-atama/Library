#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX_ROW = 510; // to be set appropriately
constexpr int MAX_COL = 510; // to be set appropriately
struct BitMatrix {
  int H, W;
  array<bitset<MAX_COL>, MAX_ROW> val;
  BitMatrix(int m = 1, int n = 1) : H(m), W(n) {}
  inline bitset<MAX_COL> &operator[](int i) { return val[i]; }
};

// is_exteneded: 拡大係数行列か？
int GaussJordan(BitMatrix &A, bool is_extended = false) {
  int rank = 0;
  for (int col = 0; col < A.W; ++col) {
    if (is_extended && col == A.W - 1) break;
    int pivot = -1;
    for (int row = rank; row < A.H; ++row) {
      if (A[row][col]) {
        pivot = row;
        break;
      }
    }
    if (pivot == -1) continue;
    swap(A[pivot], A[rank]);
    for (int row = 0; row < A.H; ++row) {
      if (row != rank && A[row][col]) A[row] ^= A[rank];
    }
    ++rank;
  }
  return rank;
}

int linear_equation(BitMatrix A, vector<int> b, vector<int> &res) {
  int m = A.H, n = A.W;
  BitMatrix M(m, n + 1);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) M[i][j] = A[i][j];
    M[i][n] = b[i];
  }
  int rank = GaussJordan(M, true);

  // check if it has no solution
  for (int row = rank; row < m; ++row)
    if (M[row][n]) return -1;

  // answer
  res.assign(n, 0);
  for (int i = 0; i < rank; ++i) res[i] = M[i][n];
  return rank;
}
