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
#define EQ(a,b) (abs((a)-(b))<eps)


// ***** 幾何ライブラリ　線分と直線に注意!! 誤差に注意すること!! *****

double add(double a,double b)
{
	if(abs(a+b)<eps*(abs(a)+abs(b)))return 0;
	return a+b;
}

struct P{
	double x,y;
	P() {}
	P(double x,double y) : x(x),y(y){}
	P operator + (P p){
		return P(add(x,p.x),add(y,p.y));
	}
	P operator - (P p){
		return P(add(x,-p.x),add(y,-p.y));
	}
	P operator * (double d){
		return P(x*d,y*d);
	}
	double dot(P p){
		return add(x*p.x,y*p.y);
	}
	double det(P p){
		return add(x*p.y,-y*p.x);
	}
	double norm(){
		return sqrt(x*x+y*y);
	}
	double norm2(){
		return x*x+y*y;
	}
	double dist2(P p){
		return sq(x-p.x)+sq(y-p.y);
	}
	P vert(){
		return P(y,-x);
	}
	void dump(){
		printf("%.12f %.12f\n",x,y);
		return;
	}
};

bool on_seg(P p1,P p2,P q)//線分p1-p2上にqがあるか
{
	return (p1-q).det(p2-q)==0&&(p1-q).dot(p2-q)<=0;
}

bool on_line(P p1,P p2,P q)//直線p1-p2上にqがあるか
{
	return (p1-q).det(p2-q)==0;
}

P intersection(P p1,P p2,P q1,P q2) //直線p1-p2と直線q1-q2の交点 平行かどうかis_parallelでcheckすること
{
	return p1+(p2-p1)*((q2-q1).det(q1-p1)/(q2-q1).det(p2-p1));
}

bool is_parallel(P p1,P p2,P q1,P q2)
{
	return (p1-p2).det(q1-q2)==0;
}

bool is_intersect(P p1,P p2,P q1,P q2)//線分p1-p2と線分q1-q2の交差判定
{
	if(p1.x>p2.x)swap(p1,p2);
	if(q1.x>q2.x)swap(q1,q2);
	P k = intersection(p1,p2,q1,q2);
	if((p1.x<=k.x)&&(k.x<=p2.x)&&(q1.x<=k.x)&&(k.x<=q2.x))return true;
	else return false;
}


bool is_intersect_line_seg(P p1,P p2,P q1,P q2)//線分p1-p2と直線q1-q2の交差判定
{
	if(p1.x>p2.x)swap(p1,p2);
	if(q1.x>q2.x)swap(q1,q2);
	P k = intersection(p1,p2,q1,q2);
	if((p1.x<=k.x)&&(k.x<=p2.x))return true;
	else return false;
}

bool is_intersect_seg_line(P p1,P p2,P q1,P q2)//直線p1-p2と線分q1-q2の交差判定
{
	if(p1.x>p2.x)swap(p1,p2);
	if(q1.x>q2.x)swap(q1,q2);
	P k = intersection(p1,p2,q1,q2);
	if((q1.x<=k.x)&&(k.x<=q2.x))return true;
	else return false;
}

int main()
{
	int Q;
	cin >> Q;
	for(int i=0;i<Q;i++)
	{
		P point[4];
		for(int i=0;i<4;i++)
		{
			cin >> point[i].x >> point[i].y;
		}
		if((point[0]-point[1]).det(point[2]-point[3])==0)
		{
			if(on_seg(point[0],point[1],point[2])||on_seg(point[0],point[1],point[3])||on_seg(point[2],point[3],point[0])||on_seg(point[2],point[3],point[1]))
			{
				cout << 1 << endl;
				continue;
			}
			else
			{
				cout << 0 << endl;
				continue;
			}
		}
		else
		{
			P r=intersection(point[0],point[1],point[2],point[3]);
			if(on_seg(point[0],point[1],r)&&on_seg(point[2],point[3],r))
			{
				cout << 1 << endl;
				continue;
			}
			else
			{
				cout << 0 << endl;
				continue;
			}
		}
	}
	return 0;
}

