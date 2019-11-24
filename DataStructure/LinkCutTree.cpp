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
// root以外はspaceships,road_developmentでverify済

// LinkCutTreeは本来、(根方向に有向な)有向木を扱うものであるから、無向木を扱う際は
// linkやcutする時に注意深くevertを行うこと。

// pathに対する様々な操作が可能。AからBへのpathに対する操作を行いたい時、
// Aをevertし、BをexposeすることでAとBは同じsplay木に含まれる様になる。
// (さらに,Bはexposeによってsplay木の根となっている)
// よって、各splay木内においてSegtree同様にデータを保持しておけば(遅延評価等も),
// 任意のpathに対するクエリに答えられる。

// is_root,rotr,rotl,splay,expose,cut,link,root,lcaはいじる必要ない。
// update,toggle,push,set,getを適宜変更して用いること。

// 対応クエリ:
// 根までのpathのコストを全てxにする
// 根までのpathのコストの和を求める

struct Node{
	Node *pp,*lp,*rp;
	int id;             // 頂点番号 初期化時に必ず指定すること。	
	int size;           // 自分の属するsplay木における自分以下の頂点数
	bool rev;           // 反転フラグ
	
	typedef int val_t;  // 適宜long longに変更すること。
	
	struct Data{
		val_t val,sum,lazy;
	}data;
	
	
	Node(int id):pp(NULL),lp(NULL),rp(NULL),id(id),size(1){}
	
	Node(int id,val_t v):pp(NULL),lp(NULL),rp(NULL),id(id){
		data.val = v;
		data.sum = v;
		data.lazy = -1;
	}
	void update(){ //子から、size,dataを更新する
		if(this==NULL)return;
		size = 1;
		data.sum = data.val;
		if(lp!=NULL){
			data.sum += lp->data.sum;
			size += lp->size;
		}
		if(rp!=NULL){
			data.sum += rp->data.sum;
			size += rp->size;
		}
		return;
	}
	void lazy_evaluate(val_t x){
		data.val = x;
		data.sum = x*size;
		data.lazy = x;
	}
	void toggle(){
		assert(this!=NULL);
		swap(lp,rp);
		rev ^= true;
	}
	void push(){
		// 遅延評価とrevフラグの伝搬を行う。
		// もちろんrevよりも先に遅延評価しないと意味がない
		bool lch = (lp!=NULL),rch = (rp!=NULL);
		if(data.lazy!=-1){
			if(lch){
				lp->lazy_evaluate(data.lazy);
			}
			if(rch){
				rp->lazy_evaluate(data.lazy);
			}
			data.lazy=-1;
		}
		if(rev){
			if(lch){
				lp->toggle();
			}
			if(rch){
				rp->toggle();
			}
			rev = false;
		}
	}
	void push_all(){ 
		// splay前に一気に根までpushする。
		// stack overflowする可能性があるので、する場合は
		// 下のsplayを使用すること。
		if(!is_root())pp->push_all();
		push();
	}
	bool is_root(){ // splay木の根か
		return !pp||(pp->lp!=this&&pp->rp!=this);
	}
	void rotr(){ // splay木　右回転
		Node *q=pp,*r=q->pp;
		if((q->lp=rp))rp->pp=q;
		rp=q;q->pp=this;
		q->update();
		update();
		if((pp=r)){
			if(r->lp==q)r->lp=this;
			if(r->rp==q)r->rp=this;
		}
		r->update();
	}
	void rotl(){ // splay木 左回転
		Node *q=pp,*r=q->pp;
		if((q->rp=lp))lp->pp=q;
		lp=q;q->pp=this;
		q->update();
		update();
		if((pp=r)){
			if(r->lp==q)r->lp=this;
			if(r->rp==q)r->rp=this;
		}
		r->update();
	}
	/*void splay(){ // splay操作。 頂点を属するsplay木の根に持っていく
		push_all();
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
	}*/
	void splay(){ // stack overflow する時用。こっちのほうが早いかも。
		push();
		while(!is_root()){
			Node *q=pp;
			if(q->is_root()){
				q->push();push();
				if(q->lp==this)rotr();
				else rotl();
			}else{
				Node *r=q->pp;
				r->push();q->push();push();
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
		// 自分の子孫とは別のsplay木に属することになる、
		// すなわちexpose後のpath分解において自分が自分を含むpathの中で最も深くなる
		// のは仕様(lca,evertが楽)
		Node *rp=NULL;
		for(Node *p=this;p;p=p->pp){
			p->splay();
			p->rp=rp;
			p->update();
			rp=p;
		}
		splay();  // 一応根に持っていっとくと色々便利(cutとかlinkの時)
	}
	
	// 無向木を扱う際、link,cut時に注意深くevertを行うこと。
	
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
	void evert(){
		//exposeで自分の子孫とは別のsplay木に属することになるからこれでOK
		expose();
		toggle();
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
	val_t get(){ // 根までのpath上のコストの和
		expose();
		return data.sum;
	}
	void set(val_t x){ // 根までのpath上のコストを全てxにする
		expose();
		lazy_evaluate(x);
	}
};
Node* nodev[100005];
Node* nodee[100005];
/*int num(Node* x){
	if(x==NULL)return -1;
	else return x->id;
}
void showtree(int n){
	for(int i=0;i<n;i++)printf("%d p %d l %d r %d rev %d\n",i,num(nodev[i]->pp),num(nodev[i]->lp),num(nodev[i]->rp),nodev[i]->rev);
}*/
int N,Q;
int main()
{
	scanf("%d %d",&N,&Q);
	for(int i=0;i<N;i++)nodev[i]=new Node(i,0);
	for(int i=0;i<N;i++)nodee[i]=new Node(i,1);
	int cnt = 0;
	for(int i=0;i<Q;i++)
	{
		int T,A,B;
		scanf("%d %d %d",&T,&A,&B);
		A--;B--;
		if(T==1){
			if((nodev[A]->lca(nodev[B]))==NULL){
				nodev[A]->evert();
				nodev[A]->link(nodee[cnt]);
				nodee[cnt]->link(nodev[B]);
				cnt++;
			}else{
				nodev[A]->evert();
				nodev[B]->set(0);
			}
		}else{
			if((nodev[A]->lca(nodev[B]))==NULL)printf("-1\n");
			else{
				nodev[A]->evert();
				printf("%d\n",nodev[B]->get());
			}
		}
	}
	return 0;
}
