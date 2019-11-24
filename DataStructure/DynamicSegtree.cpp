#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define INF 2000000000
#define pb push_back
int M,B;
const int SIZE = 1<<30;
struct DynamicSegtree{
	struct node{
		int val,lazy,l,r;
		node *lch,*rch;
		node(int left,int right){
			val = 0;
			lazy = 0;
			l = left;
			r = right;
			lch = (node*)NULL;
			rch = (node*)NULL;
		}
	};
	node *root;
	map<int,int> m;
	void init(){root = new node(0,SIZE);}
	void lazy_evaluate(node *x){
		x->val += x->lazy;
		if(((x->r)-(x->l))!=1){
			if((x->lch)==(node*)NULL)x->lch = new node(x->l,((x->l)+(x->r))/2);
			if((x->rch)==(node*)NULL)x->rch = new node(((x->l)+(x->r))/2,x->r);
			(x->lch)->lazy += x->lazy;
			(x->rch)->lazy += x->lazy;
		}
		x->lazy = 0;
	}
	//update(a,b,val) add val to [a,b)
	void update(int a,int b,int val,node *x){
		if((x->r)<=a||b<=(x->l))return;
		if(a<=(x->l)&&(x->r)<=b)x->lazy += val;
		else{
			lazy_evaluate(x);
			update(a,b,val,x->lch);
			update(a,b,val,x->rch);
			x->val = max(value(x->lch),value(x->rch));
		}
		return;
	}
	void update(int a,int b,int val){
		if(val>0)m[a]++;
		else{
			m[a]--;
			if(m[a]==0)m.erase(a);
		}
		update(a,b,val,root);
		return;
	}
	int value(node *x){return x->val+x->lazy;}
	int get_max(){return value(root);}
	void query(int x){
		//search maximum index whose number is not smaller than x 
		if(get_max()<x)printf("NO\n");
		else{
			node *cur = root;
			while((cur->lch)!=(node*)NULL||(cur->rch)!=(node*)NULL){
				lazy_evaluate(cur);
				if(value(cur->rch)>=x)cur = cur->rch;
				else if((value(cur->lch)>=x))cur = cur->lch;
			}
			int origin = (cur->r)-1;
			map<int,int>::iterator it = m.upper_bound(origin);
			vector<int> v;
			int res = x;
			while(res>0){
				it--;
				for(int i=0;i<min(res,it->second);i++)v.pb(it->first);
				res -= min(res,it->second);
			}
			for(int i=x-1;i>=0;i--){
				printf("%d%c",v[i],((i==0)?'\n':' '));
				update(v[i],min(v[i]+B+1,SIZE),-1);
			}
		}
		return;
	}
}seg;
int main(){
	seg.init();
	scanf("%d %d",&M,&B);
	for(int i=0;i<M;i++){
		char type;
		int x;
		cin >> type;
		if(type=='E')break;
		scanf("%d",&x);
		if(type=='A')seg.update(x,min(x+B+1,SIZE),1);
		else seg.query(x);
		fflush(stdout);
	}
	return 0;
}
