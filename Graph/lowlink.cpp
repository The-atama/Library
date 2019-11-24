#include <vector>
#include <algorithm>
using namespace std;
#define MAX_V 10000
vector<int> graph[MAX_V];
bool used_v[MAX_V],used_e[MAX_V][MAX_V];
int ord[MAX_V],lowlink[MAX_V];
int k=0;
void dfs(int v)
{
	used_v[v]=true;
	ord[v]=lowlink[v]=k++;
	for(int i=0;i<graph[v].size();i++)
	{
		if(!used_v[graph[v][i]])
		{
			used_e[v][graph[v][i]]=true;
			dfs(graph[v][i]);
			lowlink[v]=min(lowlink[v],lowlink[graph[v][i]]);
		}
		else if(!used_e[graph[v][i]][v])
		//then,e(v,graph[v][i]) is backward edge
		{
			lowlink[v]=min(lowlink[v],ord[graph[v][i]]);
		}
	}
	return;
}
// e(u,v) is bridge <=> ord(u) < lowlink(v)
// vが関節点 <=> ord[u] ≦ lowlink[v]となるvの子が存在する(if v != root)
//           <=> 子が2つ以上 (if v is root)

