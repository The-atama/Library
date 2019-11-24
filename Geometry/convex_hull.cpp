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
struct P{
	double x,y;
	P() {}
	P(double x,double y):x(x),y(y){}
	P operator +(P p){
		return P(add(x,p.x),add(y,p.y));
	}
	P operator -(P p){
		return P(add(x,-p.x),add(y,-p.y));
	}
	P operator *(double d){
		return P(d*x,d*y);
	}
	double dot(P p){
		return add(x*p.x,y*p.y);
	}
	double det(P p){
		return add(x*p.y,-y*p.x);
	}
};
bool comp(const P& p,const P& q){
	if(p.x!=q.x)return p.x<q.x;
	return p.y<q.y;
}
vector<P> convex_hull(P* ps,int n)
{
	sort(ps,ps+n,comp);
	int k=0;
	vector<P> qs(2*n);
	for(int i=0;i<n;i++)
	{
		while(k>1&&(qs[k-1]-qs[k-2]).det(ps[i]-qs[k-1])<=0)k--;
		qs[k++]=ps[i];
	}
	for(int i=n-2,t=k;i>=0;i--)
	{
		while(k>t&&(qs[k-1]-qs[k-2]).det(ps[i]-qs[k-1])<=0)k--;
		qs[k++]=ps[i];
	}
	qs.resize(k-1);
	return qs;
}
double dist(P p,P q){
	return (p-q).dot(p-q);
}
int n;
P v[50050];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%lf %lf",&(v[i].x),&(v[i].y));
	}
	vector<P> cv;
	cv=convex_hull(v,n);
	double ans=0;
	for(int i=0;i<cv.size();i++){
		for(int j=i+1;j<cv.size();j++){
			ans=max(ans,dist(cv[i],cv[j]));
		}
	}
	printf("%.0f\n",ans);
	return 0;
}
