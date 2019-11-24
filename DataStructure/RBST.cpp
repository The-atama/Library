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
#include <cassert>
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
typedef int val_t;
struct RBST{
	struct Node{
		Node *lp,*rp;
		int size;
		val_t val,mini;
		Node(val_t v):val(v),mini(v),size(1),lp(NULL),rp(NULL){}
	};
	Node *root;
	RBST():root(NULL){}
	int size(Node *x){return !x?0:x->size;}
	val_t mini(Node *x){return !x?INF:x->mini;}
	Node* update(Node *x){
		if(x==NULL)return x;
		x->size = 1+size(x->lp)+size(x->rp);
		x->mini = min(min(x->val,mini(x->lp)),mini(x->rp));
		return x;
	}
	Node* merge(Node* x,Node* y){
		if(x==NULL)return y;
		if(y==NULL)return x;
		int m = x->size , n = y->size;
		if(rand()%(m+n)<m){
			x->rp = merge(x->rp,y);
			return update(x);
		}else{
			y->lp = merge(x,y->lp);
			return update(y);
		}
	}
	typedef pair<Node*,Node*> Np;
	Np split(Node *x,int k){ //[0,k),[k,n)
		if(x==NULL)return Np(NULL,NULL);
		if(k<=size(x->lp)){
			Np s = split(x->lp,k);
			x->lp = s.sec;
			return mp(s.fi,update(x));
		}else{
			Np s = split(x->rp,k-size(x->lp)-1);
			x->rp = s.fi;
			return mp(update(x),s.sec);
		}
	}
	void insert(int k,val_t val){ // 0-indexed
		Np s = split(root,k);
		root = merge(merge(s.fi,new Node(val)),s.sec);
		return;
	}
	val_t erase(int k){ // 0-indexed
		Np s = split(root,k);
		Np s2 = split(s.sec,1);
		root = merge(s.fi,s2.sec);
		return s2.fi->val;
	}
	val_t query(int l,int r){ //[l,r)
		Np s = split(root,l);
		Np s2 = split(s.sec,r-l);
		val_t ret = s2.fi->mini;
		root = merge(merge(s.fi,s2.fi),s2.sec);
		return ret;
	}
	void shift(int l,int r){ //[l,r)
		Np s = split(root,l);
		Np s2 = split(s.sec,r-l);
		Np s3 = split(s2.fi,r-l-1);
		root = merge(s.fi,merge(merge(s3.sec,s3.fi),s2.sec));
		return;
	}
}tree;
int main()
{
	int N,Q;
	srand((unsigned int)time(NULL));
	scanf("%d %d",&N,&Q);
	for(int i=0;i<N;i++){
		int a;
		scanf("%d",&a);
		tree.insert(i,a);
	}
	for(int i=0;i<Q;i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		if(x==0){
			z++;
			tree.shift(y,z);
		}else if(x==1){
			z++;
			printf("%d\n",tree.query(y,z));
		}else{
			tree.erase(y);
			tree.insert(y,z);
		}
	}
	return 0;
}
