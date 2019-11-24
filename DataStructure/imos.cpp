#include <bits/stdc++.h>
using namespace std;
template<class T>
struct imos{
	vector<T> vec;
	vector<T> rui;
	imos(){}
	imos(vector<T> v){
		vec = v;
		init();
	}
	void init(){
		rui = vec;
		for(int i=1;i<rui.size();i++){
			rui[i] += rui[i-1];
		}
	}
	T sum(int l,int r){
		if(l==0)return rui[r];
		else return rui[r]-rui[l-1];
	}
};
int main(){
	vector<int> a = {1,2,4};
	imos<int> rui(a);
	cout << rui.sum(0,1) << endl;
	return 0;
}
