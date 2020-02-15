#include <bits/stdc++.h>

using namespace std;

struct UnionFind{
	vector<int> par,rank,sz;
	UnionFind(int n){
    par.assign(n,0);
    rank.assign(n,0);
    sz.assign(n,1);
		for(int i=0;i<n;i++){
			par[i] = i;
		}
	}
	int find(int x){
		if(par[x] == x)return x;
		else return par[x] = find(par[x]);
	}
	void unite(int x,int y){
		x = find(x);
		y = find(y);
		if(x==y)return;
		if(rank[x] < rank[y]){
      par[x] = y;
      sz[y] += sz[x];
    }else{
			par[y] = x;
      sz[x] += sz[y];
			if(rank[x] == rank[y])rank[x]++;
		}	
	}
	bool same(int x,int y){
		return find(x) == find(y);
	}
};
int main(){
	return 0;
}
