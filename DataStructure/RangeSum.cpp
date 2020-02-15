#include <bits/stdc++.h>

using namespace std;

template<class T>
struct RangeSum{
  vector<T> vec;
  RangeSum(){}
  RangeSum(vector<T> elems):vec(elems){
    for(int i=1;i<vec.size();i++){
      vec[i] += vec[i-1];
    }
  }
  T sum(int l,int r){
    if(l>r)return T(0);
    if(l==0)return vec[r];
    else return vec[r]-vec[l-1];
  }
};

int main(){
	vector<int> a = {1,2,4};
	RangeSum<int> rui(a);
	cout << rui.sum(0,1) << endl;
	return 0;
}
