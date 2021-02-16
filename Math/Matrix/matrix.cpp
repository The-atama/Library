#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// matrix class
// constructor of T : T(1),T(0) must be unit of T
// verified DDCC B
// https://atcoder.jp/contests/ddcc2020-final/submissions/9941022
template <class T>
struct Matrix {
  int H, W;
  vector<vector<T>> elem;
  Matrix(int H, int W, T val = T(0)) : H(H), W(W) {
    elem.resize(H);
    for (int i = 0; i < H; i++) elem[i].assign(W, val);
  }
  Matrix(const vector<vector<T>> &m)
      : H(m.size()), W(m.size() ? m[0].size() : 0) {
    elem.resize(H);
    for (int i = 0; i < H; i++) elem[i].resize(W);
    for (int i = 0; i < H; i++) elem[i] = m[i];
  }
  vector<T> &operator[](int h) { return elem[h]; }
  static Matrix identity(int N) {
    Matrix a(N, N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (i == j)
          a.elem[i][i] = T(1);
        else
          a.elem[i][j] = T(0);
      }
    }
    return a;
  }
  Matrix operator+(const Matrix &m) const {
    assert(H == m.H && W == m.W);
    Matrix a(H, W);
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        a.elem[i][j] = this->elem[i][j] + m.elem[i][j];
      }
    }
    return a;
  }
  Matrix operator-(const Matrix &m) const {
    assert(H == m.H && W == m.W);
    Matrix a(H, W);
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        a.elem[i][j] = this->elem[i][j] - m.elem[i][j];
      }
    }
    return a;
  }
  Matrix operator*(const Matrix &m) const {
    assert(W == m.H);
    Matrix a(H, m.W);
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < m.W; j++) {
        for (int k = 0; k < W; k++) {
          a.elem[i][j] = a.elem[i][j] + (this->elem[i][k] * m.elem[k][j]);
        }
      }
    }
    return a;
  }
  Matrix &operator+=(const Matrix &m) { return *this = *this + m; }
  Matrix &operator-=(const Matrix &m) { return *this = *this - m; }
  Matrix &operator*=(const Matrix &m) { return *this = *this * m; }
  Matrix pow(long long x) const {
    Matrix a = identity(H);
    Matrix b = *this;
    while (x) {
      if (x & 1) a *= b;
      b *= b;
      x >>= 1;
    }
    return a;
  }
  friend ostream &operator<<(ostream &os, const Matrix &x) {
    for (int i = 0; i < x.H; i++) {
      for (int j = 0; j < x.W; j++) {
        os << x.elem[i][j];
        if (j + 1 < x.W) cout << ' ';
      }
      if (i + 1 < x.H) cout << endl;
    }
    return os;
  }
  friend istream &operator>>(istream &is, Matrix &x) {
    for (auto &v : x.elem) is >> v;
    return is;
  }
};

// 1 1 2 3 5 8 ...
ll fib(ll x) {
  Matrix<ll> A(2, 2);
  A[0][0] = 1;
  A[0][1] = 1;
  A[1][0] = 1;
  A[1][1] = 0;
  A = A.pow(x);
  return A[1][0];
}

int main() {
  cout << fib(30) << endl;
  return 0;
}
