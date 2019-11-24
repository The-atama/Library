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
typedef char val_t;
const int memory_limit = 20000000;
struct RBST{
	struct Node{
		Node *lp,*rp;
		int size;
		val_t val;
		Node(){}
		Node(val_t v):val(v),size(1),lp(NULL),rp(NULL){}
		Node(Node* x):val(x->val),size(x->size),lp(x->lp),rp(x->rp){}
	};
	Node *root;
	RBST():root(NULL),memory_size(0){}
	Node pool[memory_limit+10000];
	int memory_size;
	char str[1000100];
	int length_limit;
	int id;
	int size(Node *x){return !x?0:x->size;}
	Node* update(Node *x){
		if(x==NULL)return x;
		x->size = 1+size(x->lp)+size(x->rp);
		return x;
	}
	Node* alloc(val_t val){
		return &(pool[memory_size++]=Node(val));
	}
	Node* copy(Node* x){
		return &(pool[memory_size++]=Node(x));
	}
	Node* merge(Node* x,Node* y){
		if(x==NULL)return y;
		if(y==NULL)return x;
		int m = x->size , n = y->size;
		if(rand()%(m+n)<m){
			x = copy(x);
			x->rp = merge(x->rp,y);
			return update(x);
		}else{
			y = copy(y);
			y->lp = merge(x,y->lp);
			return update(y);
		}
	}
	Node* merge_(Node* x,Node* y){
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
		x = copy(x);
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
		root = merge(merge(s.fi,alloc(val)),s.sec);
		return;
	}
	val_t erase(int k){ // 0-indexed
		Np s = split(root,k);
		Np s2 = split(s.sec,1);
		root = merge(s.fi,s2.sec);
		return s2.fi->val;
	}
	void copypaste(int a,int b,int c){ // 0-indexed [a,b) 
		Np s = split(root,a);
		Np s2 = split(s.sec,b-a);
		Np s3 = split(root,c);
		root = merge(merge(s3.fi,s2.fi),s3.sec);
		if(size(root)>length_limit)root = split(root,length_limit).fi;
		return;
	}
	void write(Node *x){
		if(x==NULL)return;
		write(x->lp);
		str[id++]=x->val;
		write(x->rp);
	}
	void build(){
		memory_size=0;
		root=NULL;
		int len = strlen(str);
		for(int i=0;i<len;i++)root=merge_(root,alloc(str[i]));
	}
	void rebuild(){
		id=0;
		write(root);
		str[id]='\0';
		build();
	}
}tree;
int main()
{
	int N,M;
	scanf("%d",&M);
	tree.length_limit = M;
	scanf("%s",tree.str);
	tree.build();
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		tree.copypaste(a,b,c);
		if(tree.memory_size>memory_limit)tree.rebuild();
	}
	tree.rebuild();
	printf("%s\n",tree.str);
	return 0;
}
