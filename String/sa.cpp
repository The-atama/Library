#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <iostream>
#include <map>
#include <set>
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
#define EQ(a,b) (abs((a)-(b))<EPS)
string s;
int sa[100100],rank[100100],tmp[100100],lcp[100100];
int n,k;
bool compare_sa(int i,int j)
{
	if(rank[i]!=rank[j])return rank[i]<rank[j];
	else
	{
		int ri=(i+k<=n)?rank[i+k]:-1;
		int rj=(j+k<=n)?rank[j+k]:-1;
		return ri<rj;
	}
}
void construct_sa()
{
	n=s.size();
	for(int i=0;i<=n;i++)
	{
		rank[i]=(i<n)?s[i]:-1;
		sa[i]=i;
	}
	for(k=1;k<=n;k*=2)
	{
		sort(sa,sa+n+1,compare_sa);
		tmp[sa[0]]=0;
		for(int i=1;i<=n;i++)tmp[sa[i]]=tmp[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0);
		for(int i=0;i<=n;i++)rank[i]=tmp[i];
	}
	return;
}
void construct_lcp()
{
	for(int i=0;i<=n;i++)rank[sa[i]]=i;
	int h=0;
	lcp[0]=0;
	for(int i=0;i<n;i++)
	{
		int j=sa[rank[i]-1];
		if(h>0)h--;
		for(;i+h<n&&j+h<n;h++)if(s[i+h]!=s[j+h])break;
		lcp[rank[i]-1]=h;
	}
	return;
}
int main()
{
	cin >> s;
	construct_sa();
	construct_lcp();
	for(int i=0;i<=n;i++)
	{
		cout << sa[i]  <<  ' ' << lcp[i] << endl;
	}
	return 0;
}
