#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
#define pb push_back
vector<int> G[10010],rG[10010];
vector<int> vs;
int V,E,Q;
bool used[10010];
int cmp[10010];
void add_edge(int from,int to)
{
    G[from].pb(to);
    rG[to].pb(from);
    return;
}
void dfs(int s)
{
    used[s]=true;
    for(int i=0;i<G[s].size();i++)
    {
        if(!used[G[s][i]])dfs(G[s][i]);
    }
    vs.pb(s);
}
void rdfs(int s,int k)
{
    used[s]=true;
    cmp[s]=k;
    for(int i=0;i<rG[s].size();i++)
    {
        if(!used[rG[s][i]])rdfs(rG[s][i],k);
    }
}
int scc()
{
    memset(used,0,sizeof(used));
    vs.clear();
    for(int v=0;v<V;v++)
    {
        if(!used[v])dfs(v);
    }
    memset(used,0,sizeof(used));
    int k=0;
    for(int i=vs.size()-1;i>=0;i--)
    {
        if(!used[vs[i]])rdfs(vs[i],k++);
    }
    return k;
}
int same(int u,int v)
{
    if(cmp[u]==cmp[v])return 1;
    else return 0;
}
int main()
{
    cin >> V >> E;
    for(int i=0;i<E;i++)
    {
        int s,t;
        cin >> s >> t;
        add_edge(s,t);
    }
    scc();
    cin >> Q;
    for(int i=0;i<Q;i++)
    {
        int u,v;
        cin >> u >> v;
        cout << same(u,v) << endl;
    }
    return 0;
}
