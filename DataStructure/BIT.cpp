#include <bits/stdc++.h>

using namespace std;

template<class T>
struct BIT{
  int N;
  vector<T> bit;
  BIT(int N):N(N){
    bit = vector<T>(N+1,T(0));
  }
  void add(int i,T x){
    i++;
    while(i<=N){ bit[i]+=x; i+=i&-i; }
    return;
  }
  T sum(int i){
    i++;
    T res = T(0);
    while(i>0){ res+=bit[i]; i-=i&-i; }
    return res;
  }
  T sum(int l,int r){// [l,r]
    assert(l<=r);
    if(l==0)return sum(r);
    else return sum(r)-sum(l-1);
  }
};

