#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <iostream>
#include <map>
#include <set>
using namespace std;
typedef pair<int,int> P;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
#define pu push
#define pb push_back
#define mp make_pair
#define eps 1e-9
#define INF 2000000000
#define sz(x) ((int)(x).size())
#define fi first
#define sec second
#define SORT(x) sort((x).begin(),(x).end())
#define all(x) (x).begin(),(x).end()
#define rep(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define repn(i,a,n) for(int (i)=(a);(i)<(int)(n);(i)++)
#define EQ(a,b) (abs((a)-(b))<eps)
// Codeforces #276 E Sign on Fence
struct node{
	node *lch,*rch;
	int l,r,mid;
	bool all;
	node(){}
	node(node *lch_,node *rch_,int x){
		lch = lch_;
		rch = rch_;
		l = r = mid = x;
		all = x?true:false;
	}
	node(node *lch_,node *rch_){
		lch = lch_;
		rch = rch_;
		all = (lch->all) & (rch->all);
		l = lch->l;
		r = rch->r;
		if(lch->all)l += rch->l;
		if(rch->all)r += lch->r;
		mid = max(max(lch->mid,rch->mid),lch->r+rch->l);
	}
};
const int SIZE = 2000000;
node pool[SIZE];
node *root[100100];
node *nil;
int pool_pos=0;
node* mynew(node *lch,node *rch,int x){
	return &(pool[pool_pos++] = node(lch,rch,x));
}
node* mynew(node *lch,node *rch){
	return &(pool[pool_pos++] = node(lch,rch));
}
node* add(node* v,int pos,int l,int r){
	if(r-l==1)return mynew(nil,nil,1);
	int mid = (l+r)/2;
	if(pos<mid)return mynew(add(v->lch,pos,l,mid),v->rch);
	else return mynew(v->lch,add(v->rch,pos,mid,r));
}
int mx,tmp;
void query(node* v,int a,int b,int l,int r){
	if(v==nil){
		tmp=0;
		return;
	}
	if(r<=a||b<=l)return;
	if(a<=l&&r<=b){
		mx = max(mx,v->mid);
		mx = max(mx,v->l+tmp);
		if(v->all)tmp+=v->mid;
		else tmp=v->r;
		return;
	}
	query(v->lch,a,b,l,(l+r)/2);
	query(v->rch,a,b,(l+r)/2,r);
}
int N,m;
int query(node* v,int a,int b){
	mx = 0;
	tmp = 0;
	query(v,a,b,0,N);
	return mx;
}
int h[100100];
vector<int> vs;
vector<int> xs[100100];
int main(){
	nil = mynew(NULL,NULL,0);
	nil->lch = nil;
	nil->rch = nil;
	scanf("%d",&N);
	root[0]=nil;
	for(int i=0;i<N;i++){
		scanf("%d",&h[i]);
		vs.pb(h[i]);
	}
	sort(all(vs));
	vs.erase(unique(all(vs)),vs.end());
	for(int i=0;i<N;i++)h[i]=lower_bound(all(vs),h[i])-vs.begin();
	for(int i=0;i<N;i++)xs[h[i]].pb(i);
	int num = vs.size();
	for(int i=0;i<num;i++){
		root[i+1]=root[i];
		for(int j=0;j<xs[num-i-1].size();j++)root[i+1]=add(root[i+1],xs[num-i-1][j],0,N);
	}
	scanf("%d",&m);
	/*while(1){
		int m,l,r;
		cin  >> m >> l >> r;
		cout << query(root[m],l,r) << endl;
	}*/
	for(int i=0;i<m;i++){
		int l,r,w;
		scanf("%d %d %d",&l,&r,&w);
		l--;
		int L=0,R=num;
		while(R-L>1){
			int mid = (L+R)/2;
			if(query(root[mid],l,r)>=w)R = mid;
			else L = mid;
			//cout << L << ' ' << R << ' ' << mx << endl;
		}
		printf("%d\n",vs[num-R]);
	}
	return 0;
}
