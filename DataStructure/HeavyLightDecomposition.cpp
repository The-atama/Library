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
#define MAX_N 150100
#define MAX_LOG_V 20
 
const int SIZE = 1<<18;
struct segtree{
    ll seg[SIZE*2],lazy[SIZE*2];
    void lazy_evaluate(int k,int l,int r){
        seg[k]+=lazy[k]*(ll)(r-l);
        if(k<SIZE-1){
            lazy[k*2+1]+=lazy[k];
            lazy[k*2+2]+=lazy[k];
        }
        lazy[k]=0ll;
    }
    void update(int a,int b,int k,int l,int r,ll x){
        lazy_evaluate(k,l,r);
        if(r<=a||b<=l)return;
        else if(a<=l&&r<=b){
            lazy[k]+=x;
            lazy_evaluate(k,l,r);
            return;
        }else{
            update(a,b,k*2+1,l,(l+r)/2,x);
            update(a,b,k*2+2,(l+r)/2,r,x);
            seg[k] = seg[k*2+1]+seg[k*2+2];
        }
    }
    void update(int a,int b,ll x){
        update(a,b,0,0,SIZE,x);
    }
    ll query(int a,int b,int k,int l,int r){
        lazy_evaluate(k,l,r);
        if(r<=a||b<=l)return 0ll;
        else if(a<=l&&r<=b)return seg[k];
        else{
            ll lch = query(a,b,k*2+1,l,(l+r)/2);
            ll rch = query(a,b,k*2+2,(l+r)/2,r);
            seg[k] = seg[k*2+1]+seg[k*2+2];
            return lch+rch;
        }
    }
    ll query(int a,int b){
        return query(a,b,0,0,SIZE);
    }
}seg;
struct HeavyLightDecomposition{
    vector<int> g[MAX_N];
    int N,root;
    int par[MAX_N];
    int depth[MAX_N],chnum[MAX_N];
    void add_edge(int a,int b){
        g[a].pb(b);
        g[b].pb(a);
    }
    struct state{
        int v,p,d;
        bool go;
        state(int v,int p,int d,bool go):v(v),p(p),d(d),go(go){}
        state(int v,int p,bool go):v(v),p(p),go(go){}
    };
    void init(){
        dfs();
        decompose();
        construct_toseg();
    }
    void dfs(){
        stack<state> st;
        st.push(state(0,-1,0,true));
        while(!st.empty()){
            state now = st.top();
            st.pop();
            int v = now.v,p = now.p,d = now.d;
            if(now.go){
                depth[v]=d;
                par[v]=p;
                st.push(state(v,p,d,false));
                for(int i=0;i<g[v].size();i++){
                    if(g[v][i]==p)continue;
                    st.push(state(g[v][i],v,d+1,true));
                }
            }else{
                chnum[v]=1;
                for(int i=0;i<g[v].size();i++){
                    chnum[v]+=chnum[g[v][i]];
                }
            }
        }
        return;
    }
    vector<int> top;
    int head[MAX_N];
    int heavy[MAX_N];
    int toseg[MAX_N];
    int chain_len[MAX_N];
    void decompose(){
        stack<state> st;
        st.push(state(0,-1,true));
        while(!st.empty()){
            state now = st.top();
            st.pop();
            int v=now.v,p=now.p,istop=now.go;
            if(istop)top.pb(v);
            int hev = -1;
            int val = -1;
            for(int i=0;i<g[v].size();i++){
                if(g[v][i]==p)continue;
                if(val<chnum[g[v][i]]){
                    val = chnum[g[v][i]];
                    hev = g[v][i];
                }
            }
            heavy[v]=hev;
            for(int i=0;i<g[v].size();i++){
                if(g[v][i]==p)continue;
                if(g[v][i]==hev)st.push(state(g[v][i],v,false));
                else st.push(state(g[v][i],v,true));
            }
        }
    }
    void construct_toseg(){
        int id = 0;
        for(int i=0;i<top.size();i++){
            int now = top[i];
            while(1){
                if(now==-1)break;
                toseg[now]=id++;
                head[now]=top[i];
                now = heavy[now];
                chain_len[top[i]]++;
            }
        }
    }
    int lca(int u,int v){
        while(head[u]!=head[v]){
            if(depth[head[u]]<depth[head[v]])swap(u,v);
            u = par[head[u]];
        }
        return (depth[u]<depth[v])?u:v;
    }
    void add(int v,ll x){
        seg.update(toseg[v],toseg[head[v]]+chain_len[head[v]],x);
    }
 
    ll solve(int v){
        ll ret = 0ll;
        int now = v;
        while(now!=-1){
            ret += seg.query(toseg[head[now]],toseg[now]);
            now = par[head[now]];
            if(now!=-1)ret += seg.query(toseg[now],toseg[now]+1)*(ll)(depth[v]-depth[now]);
        }
        return ret;
    }
    ll query(int u,int v){
        int lc = lca(u,v);
        return solve(u)+solve(v)-solve(lc)*2ll;
    }
}hld;
 
int N,Q;
int main(){
    /*while(1){
        int t,u,v,x;
        scanf("%d %d %d",&t,&u,&v);
        if(t==0)printf("%lld\n",seg.query(u,v));
        else{
            scanf("%d",&x);
            seg.update(u,v,x);
        }
    }*/
    scanf("%d %d",&N,&Q);
    hld.N = N;
    for(int i=0;i<N-1;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        hld.add_edge(a,b);
    }
    hld.root = 0;
    hld.init();
    /*for(int i=0;i<N;i++){
        printf("%d %d %d %d %d\n",i,head[i],heavy[i],toseg[i],chain_len[i]);
    }*/
    for(int i=0;i<Q;i++){
        int t,u,v;
        scanf("%d %d %d",&t,&u,&v);
        if(t==0)printf("%lld\n",hld.query(u,v));
        else hld.add(u,v);
    }
    return 0;
}
