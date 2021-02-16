// ax + by = gcd(a, b)
template <typename T>
T extgcd(T a, T b, T &x, T &y) {
  if (b != 0) {
    T g = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
  } else {
    x = 1;
    y = 0;
    return a;
  }
}
