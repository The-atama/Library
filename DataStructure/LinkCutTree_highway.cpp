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

// lca()は、基本的にLCAを求めよというクエリ以外では用いない。
// LinkCutTreeではevertすることでクエリを根からの一直線なpathのクエリに直せることを意識せよ。

// is_root,rotr,rotl,splay,expose,cut,link,root,lcaはいじる必要ない。
// update,toggle,push,set,getを適宜変更して用いること。

// 対応クエリ:
// 辺の両方向のコストを指定する
// 根までのpathのコストの和を求める

struct Node{
	Node *pp,*lp,*rp;
	int id;             // 頂点番号 初期化時に必ず指定すること。	
	int size;           // 自分の属するsplay木における自分以下の頂点数
	bool rev;           // 反転フラグ
	
	typedef int val_t;  // 適宜long longに変更すること。
	
	struct Data{
		val_t up,sum_up,down,sum_down;
	}data;
	
	
	Node(int id):pp(NULL),lp(NULL),rp(NULL),id(id),size(1){}
	
	Node(int id,val_t v):pp(NULL),lp(NULL),rp(NULL),id(id){
		data.up = data.sum_up = data.down = data.sum_down = v;
	}
	void update(){ //子から、size,dataを更新する
		if(this==NULL)return;
		size = 1;
		data.sum_up = data.up;
		data.sum_down = data.down;
		if(lp!=NULL){
			data.sum_up += lp->data.sum_up;
			data.sum_down += lp->data.sum_down;
			size += lp->size;
		}
		if(rp!=NULL){
			data.sum_up += rp->data.sum_up;
			data.sum_down += rp->data.sum_down;
			size += rp->size;
		}
		return;
	}
	// 左右の子を反転させて変わる値がある時はtoggleでいじるのを忘れないこと。
	void toggle(){
		assert(this!=NULL);
		swap(lp,rp);
		swap(data.up,data.down);
		swap(data.sum_up,data.sum_down);
		rev ^= true;
	}
	void push(){
		// 遅延評価とrevフラグの伝搬を行う。
		// もちろんrevよりも先に遅延評価しないと意味がない
		bool lch = (lp!=NULL),rch = (rp!=NULL);
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
		splay();  // 一応根に持っていっとくと色々便利(cutとかlinkとか遅延評価の時)
	}
	
	// 無向木を扱う際、link,cut時に注意深くevertを行うこと。
	
	void cut(){ // 実際の木において親への辺をcut
		expose();
		Node *p=lp;
		if(p!=NULL){
			lp=NULL;
			p->pp=NULL;
		}
		update();
	}
	void link(Node *p){ // 実際の木においてpへ辺を張る(pのほうが親)
		assert(this!=p);
		expose();       // 既に同じ木に属してるもの同士をlinkするとヤバいから注意。
		p->expose();
		pp=p;           // 両方向にリンクを張ってもいいが、updateが面倒
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
		return data.sum_up;
	}
	void set(val_t u,val_t d){ // コストをxにする
		expose();
		data.up = u;
		data.down = d;
		update();
	}
};
Node* nv[100100];
Node* ne[100100];
/*int num(Node* x){
	if(x==NULL)return -1;
	else return x->id;
}
void showtree(int n){
	for(int i=0;i<n;i++)printf("%d p %d l %d r %d rev %d\n",i,num(nv[i]->pp),num(nv[i]->lp),num(nv[i]->rp),nv[i]->rev);
}*/
int N,M;
int p[100100],q[100100];
int main()
{
	scanf("%d %d",&N,&M);
	for(int i=0;i<N;i++)nv[i]=new Node(i,0);
	for(int i=0;i<N-1;i++)ne[i]=new Node(i,1);
	for(int i=0;i<N-1;i++){
		scanf("%d %d",&p[i],&q[i]);
		if(p[i]>q[i])swap(p[i],q[i]);
		p[i]--;q[i]--;
		nv[p[i]]->evert();
		nv[p[i]]->link(ne[i]);
		ne[i]->link(nv[q[i]]);
	}
	for(int i=0;i<M;i++)
	{
		char T;
		int r,s,t,x,y;
		scanf(" %c",&T);
		if(T=='I'){
			scanf("%d %d %d",&r,&s,&t);
			r--;
			nv[q[r]]->evert();
			ne[r]->set(s,t);
		}else{
			scanf("%d %d",&x,&y);
			x--;y--;
			nv[y]->evert();
			printf("%d\n",nv[x]->get());
		}
	}
	return 0;
}
