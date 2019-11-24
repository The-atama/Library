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
// Link Cut Tree
// 木をHeavy-Light decompositionし、各pathをsplay木(平衡二分木)で管理
// 各splay木において、左にあるほど根に近い。
// root以外はspaceshipsでverify済
struct Node{
	Node *pp,*lp,*rp;
	int id;
	Node():pp(NULL),lp(NULL),rp(NULL){}
	Node(int id):pp(NULL),lp(NULL),rp(NULL),id(id){}
	bool is_root(){ // splay木の根か
		return !pp||(pp->lp!=this&&pp->rp!=this);
	}
	void rotr(){ // splay木　右回転
		Node *q=pp,*r=q->pp;
		if((q->lp=rp))rp->pp=q;
		rp=q;q->pp=this;
		if((pp=r)){
			if(r->lp==q)r->lp=this;
			if(r->rp==q)r->rp=this;
		}
	}
	void rotl(){ // splay木 左回転
		Node *q=pp,*r=q->pp;
		if((q->rp=lp))lp->pp=q;
		lp=q;q->pp=this;
		if((pp=r)){
			if(r->lp==q)r->lp=this;
			if(r->rp==q)r->rp=this;
		}
	}
	void splay(){ // splay操作。 頂点を属するsplay木の根に持っていく
		while(!is_root()){
			Node *q=pp;
			if(q->is_root()){
				if(q->lp==this)rotr();
				else rotl();
			}else{
				Node *r=q->pp;
				if(r->lp==q){
					if(q->lp==this){q->rotr();rotr();}
					else {rotl();rotr();}
				}else{
					if(q->rp==this){q->rotl();rotl();}
					else {rotr();rotl();}
				}
			}
		}
	}
	void expose(){ // 実際の木の根を含むsplay木に属する様に変形する
		Node *rp=NULL;
		for(Node *p=this;p;p=p->pp){
			p->splay();
			p->rp=rp;
			rp=p;
		}
		splay();  // 一応根に持っていっとくと色々便利(cutとかlinkの時)
	}
	void cut(){ // 実際の木において親への辺をcut
		expose();
		Node *p=lp;
		if(p!=NULL){
			lp=NULL;
			p->pp=NULL;
		}
	}
	void link(Node *p){ // 実際の木においてpへ辺を張る(pのほうが親)
		expose();       // 既に同じ木に属してるもの同士をlinkするとヤバいから注意。
		p->expose();
		pp=p;
		p->rp=this;
	}
	Node* root(){ // 実際の木において、このnodeが所属する木の根
		expose();
		Node* u = this;
		while(u->lp)u=u->lp;
		u->splay();
		return u;
	}
	Node* lca(Node *p){
		p->expose();
		expose();
		Node *ret=p;
		while(p->pp != NULL){
			//exposeで自分の子孫とは別のsplay木に属することになるからこれでOK
			if(p->is_root())ret=p->pp;
			p=p->pp;
		}
		return (this==p)?ret:NULL;
	}
};

Node* node[1000005];

int N,Q;
int main()
{
	scanf("%d %d",&N,&Q);
	for(int i=0;i<N;i++)node[i]=new Node(i);
	for(int i=0;i<Q;i++)
	{
		int T,A,B;
		scanf("%d",&T);
		if(T==1){
			scanf("%d %d",&A,&B);
			A--;B--;
			node[A]->link(node[B]);
		}else if(T==2){
			scanf("%d",&A);
			A--;
			node[A]->cut();
		}else{
			scanf("%d %d",&A,&B);
			A--;B--;
			Node *lc = node[A]->lca(node[B]);
			if(lc==NULL)printf("-1\n");
			else printf("%d\n",(lc->id)+1);
		}
	}
	return 0;
}
