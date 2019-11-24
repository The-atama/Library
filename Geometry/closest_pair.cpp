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
typedef long long ll;
typedef pair<short,short> P;
typedef vector<int> vi;
typedef vector<ll> vll;
#define pu push
#define pb push_back
#define mp make_pair
#define eps 1e-9
#define INF 1000000000000000000ll
#define sz(x) ((int)(x).size())
#define fi first
#define sec second
#define SORT(x) sort((x).begin(),(x).end())
#define all(x) (x).begin(),(x).end()
#define EQ(a,b) (abs((a)-(b))<EPS)
#define MAX_N 100000000
int N;
vector<P> A;
bool comp(P a,P b){return a.sec<b.sec;}
ll closest_pair(vector<P> a,int n)
{
	if(n<=1)return INF;
	int m=n/2;
	ll x=(ll)a[m].fi;
	ll d=min(closest_pair(a,m),closest_pair(a,n-m));
	inplace_merge(a.begin(),a.begin()+m,a.begin()+n,comp);
	vector<P> b;
	for(int i=0;i<n;i++)
	{
		if(abs((ll)a[i].fi-(ll)x)>=d)continue;
		for(int j=0;j<b.size();j++)
		{
			ll dx=(ll)a[i].fi-(ll)b[b.size()-1-j].fi;
			ll dy=(ll)a[i].sec-(ll)b[b.size()-1-j].sec;
			if(dy>=d)break;
			d=min(d,dx*dx+dy*dy);
		}
		b.pb(a[i]);
	}
	return d;
}
int main()
{
	cin >> N;
	for(int i=0;i<N;i++)
	{
		P in;
		cin >> in.fi >> in.sec;
		A.pb(in);
	}
	sort(A.begin(),A.begin()+N);
	cout << closest_pair(A,N) << endl;
	return 0;
}
