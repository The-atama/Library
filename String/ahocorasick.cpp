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

// Aho-Corasick

#define SIZE 256

struct Trie{
	Trie* child[SIZE];
	Trie* fail;
	vector<int> matched;
	Trie(){
		for(int i=0;i<SIZE;i++)child[i]=NULL;
		fail = NULL;
	}
	~Trie(){}
};
Trie pool[5000];
int pool_pos;
inline Trie* alloc(){return &(pool[pool_pos++]=Trie());}
inline void destruct(){pool_pos=0;}
vector<int> unite(const vector<int> &a,const vector<int> &b){
	vector<int> ret;
	set_union(all(a),all(b),back_inserter(ret));
	return ret;
}
Trie* build(vector<string> pattern){
	Trie *root = alloc();
	Trie *now;
	root->fail = root;
	for(int i=0;i<pattern.size();i++){
		now = root;
		for(int j=0;j<pattern[i].size();j++){
			int idx = (int)pattern[i][j];
			if(now->child[idx]==NULL){
				now->child[idx]=alloc();
			}
			now = now->child[idx];
		}
		now->matched.pb(i);
	}
	queue<Trie*> q;
	for(int i=0;i<SIZE;i++){
		if((root->child[i])==NULL)root->child[i]=root;
		else{
			root->child[i]->fail=root;
			q.push(root->child[i]);
		}
	}
	while(!q.empty()){
		now = q.front();q.pop();
		for(int i=0;i<SIZE;i++){
			if(now->child[i]){
				Trie *next = now->fail;
				while((next->child[i])==NULL)next=next->fail;
				now->child[i]->fail = next->child[i];
				now->child[i]->matched = unite(now->child[i]->matched,next->child[i]->matched);
				q.push(now->child[i]);
			}
		}
	}
	return root;
}
// nowを途中のノードにすることで続きからも検索可能
// retをpatternの要素数で初期化すること。
// nowは参照渡しなのでコピーしてから渡すこと。
void match(Trie* &now,const string s,vector<int> &ret){
	for(int i=0;i<s.size();i++){
		int idx = s[i];
		while((now->child[idx])==NULL)now=now->fail;
		now=now->child[idx];
		for(int j=0;j<(now->matched.size());j++){
			ret[now->matched[j]]=1;
		}
	}
}
struct state{
	P pos;
	Trie* trie;
	int turn;
	state(P pos,Trie* trie,int turn):pos(pos),trie(trie),turn(turn){}
};
int dx[4]={0,-1,0,1};
int dy[4]={1,0,-1,0};
string dv[4]={"D","L","U","R"};
string f[55];
int main(){
	while(1){
		int n,m,p;
		P S,G;
		set<Trie*> s[55][55];
		scanf("%d %d",&n,&m);
		if(n==0&&m==0)break;
		for(int i=0;i<n;i++)cin >> f[i];
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(f[i][j]=='S'){S=P(j,i);}
				if(f[i][j]=='G'){G=P(j,i);}
			}
		}
		scanf("%d",&p);
		vector<string> pat(p);
		for(int i=0;i<p;i++)cin >> pat[i];
		destruct();
		Trie* root = build(pat);
		/*while(1){
			string s;
			cin >> s;
			vector<int> v(p,0);
			Trie* r = root;
			match(r,s,v);
			int flag = 0;
			for(int i=0;i<p;i++)flag|=v[i];
			if(flag)printf("exist\n");
			else printf("not exist\n");
		}*/
		queue<state> q;
		q.push(state(S,root,0));
		int ans = -1;
		while(!q.empty()){
			state now = q.front(); q.pop();
			if(now.pos == G){ans = now.turn;break;}
			int x = now.pos.fi , y = now.pos.sec;
			for(int i=0;i<4;i++){
				int nx = x + dx[i];
				int ny = y + dy[i];
				if(nx<0||nx>=m||ny<0||ny>=n)continue;
				if(f[ny][nx]=='#')continue;
				vector<int> v(p,0);
				Trie* t = now.trie;
				match(t,dv[i],v);
				int flag = 0;
				for(int j=0;j<p;j++)flag|=v[j];
				if(flag)continue;
				if(s[nx][ny].find(t)==s[nx][ny].end()){
					s[nx][ny].insert(t);
					q.push(state(P(nx,ny),t,now.turn+1));
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

