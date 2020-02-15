#include <bits/stdc++.h>

using namespace std;

// Contents
//
// digit     : number of digits
// digit_sum : sum of all digits
// mygcd     : gcd

template<class T>
int digit(T x){
  int res = 0;
  while(x){ x /= T(10); res++; }
  return res;
}

template<class T>
int digit_sum(T x){
  int res = 0;
  while(x){ res+=x%10; x/=10; }
  return res;
}

template<class T>
T mygcd(T x,T y){
  if(y==T(0))return x;
  else return mygcd(y,x%y);
}
