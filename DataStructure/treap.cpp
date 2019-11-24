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
struct node{
	int val;     // value of this node
	double pri;  // priority selected randomly
	int size;    // size of tree
	int mini;     // min,max,sum etc.
	node *lch,*rch;
	node(int v,double p):val(v),pri(p),size(1),mini(v){
		lch = NULL;
		rch = NULL;
	}
};
typedef pair<node*,node*> Np;
int size(node *v){return !v?0:v->size;}
int mini(node *v){return !v?INF:v->mini;}
node* update(node *v){
	v->size = size(v->lch)+size(v->rch)+1;
	v->mini = min(min(mini(v->lch),mini(v->rch)),v->val);
	return v;
}
node* merge(node *l,node *r){
	if(!l||!r)return !l?r:l;
	if(l->pri > r->pri){
		l->rch = merge(l->rch,r);
		return update(l);
	}else{
		r->lch = merge(l,r->lch);
		return update(r);
	}
}
Np split(node *v,int k) //[0,k),[k,n){
	if(!v)return Np(NULL,NULL);
	if(k<=size(v->lch)){
		Np s = split(v->lch,k);
		v->lch = s.sec;
		return mp(s.fi,update(v));
	}else{
		Np s = split(v->rch,k-size(v->lch)-1);
		v->rch = s.fi;
		return mp(update(v),s.sec);
	}
}
node* insert(node* v,int k,int val,double pri){
	if(!v)return new node(val,pri);
	Np s = split(v,k);
	node* x = new node(val,pri);
	return merge(merge(s.fi,x),s.sec);
}
//jissou kaizen no yochi ari.(kesareta node wo delete) 
Np erase(node* v,int k) // remain,erased
{
	Np sr = split(v,k+1);
	Np sl = split(sr.fi,k);
	return mp(merge(sl.fi,sr.sec),sl.sec);
}
node *root;
int n,q;
int main(){
	srand((unsigned int)time(NULL));
	scanf("%d %d",&n,&q);
	root = NULL;
	for(int i=0;i<n;i++){
		int x;
		scanf("%d",&x);
		root = insert(root,i,x,(double)rand());
	}
	for(int i=0;i<q;i++){
		int type,l,r,pos,val;
		scanf("%d %d %d",&type,&l,&r);
		pos = l;
		val = r;
		if(type==0){
			Np s1 = split(root,l);
			Np s2 = split(s1.sec,r-l+1);
			Np s3 = split(s2.fi,r-l);
			root = merge(merge(s1.fi,merge(s3.sec,s3.fi)),s2.sec);
		}else if(type==1){
			Np s1 = split(root,l);
			Np s2 = split(s1.sec,r-l+1);
			printf("%d\n",mini(s2.fi));
			root = merge(s1.fi,merge(s2.fi,s2.sec));
		}else{
			Np s1 = split(root,pos);
			Np s2 = split(s1.sec,1);
			node* newnode = new node(val,(double)rand());
			root = merge(merge(s1.fi,newnode),s2.sec);
		}
	}
	return 0;
}
