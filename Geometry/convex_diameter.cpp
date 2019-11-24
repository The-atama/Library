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
#include <iomanip>
using namespace std;
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
double add(double a,double b)
{
	if(abs(a+b)<eps*(abs(a)+abs(b)))return 0;
	return a+b;
}
struct P
{
	double x,y;
	P (){}
	P(double x,double y):x(x),y(y){}
	P operator +(P p)
	{
		return P(add(x,p.x),add(y,p.y));
	}
	P operator -(P p)
	{
		return P(add(x,-p.x),add(y,-p.y));
	}
	P operator *(double d)
	{
		return P(x*d,y*d);
	}
	double dot(P p)
	{
		return add(x*p.x,y*p.y);
	}
	double det(P p)
	{
		return add(x*p.y,-y*p.x);
	}
};
bool comp(const P& p,const P& q)
{
	if(p.x!=q.x)return p.x<q.x;
	return p.y<q.y;
}
double dist(P p,P q)
{
	return sqrt((p-q).dot(p-q));
}
int main()
{
	vector<P> cv;
	int n;
	cin >> n;
	for(int i=0;i<n;i++)
	{
		P a;
		cin >> a.x >> a.y;
		cv.pb(a);
	}
	int i=0,j=0;
	for(int k=0;k<n;k++)
	{
		if(!comp(cv[i],cv[k]))i=k;
		if(comp(cv[j],cv[k]))j=k;
	}
	int si=i,sj=j;
	double ans=0;
	while(i!=sj||j!=si)
	{
		ans=max(ans,dist(cv[i],cv[j]));
		if((cv[(i+1)%n]-cv[i]).det(cv[(j+1)%n]-cv[j])<0)i=(i+1)%n;
		else j=(j+1)%n;
	}
	cout << setprecision(16) << ans << endl;
	return 0;
}
