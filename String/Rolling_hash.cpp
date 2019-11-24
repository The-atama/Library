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
#include <iostream>
#include <map>
#include <set>
using namespace std;
typedef pair<int,int> P;
typedef long long ll;
typedef unsigned long long ull;
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
struct Rolling_hash
{
	Rolling_hash(string str)
	{
		p = str;
		ps = (int)str.size();
	}
	string p;
	int ps;
	ll hash_A[1000100],hash_B[1000100];
	ll rui_A[1000100],rui_B[1000100];
	static const ll A = 1145141919ll;
	static const ll B = 810893ll;
	static const ll MOD = 1000000007ll; // should be prime (the bigger,the better)
	ll plus_(ll a,ll b)
	{
		return (a+b)%MOD;
	}
	ll minus_(ll a,ll b)
	{
		return ((a-b)%MOD+MOD)%MOD;
	}
	ll mul_(ll a,ll b)
	{
		return (a*b)%MOD;
	}
	void culc_hash()
	{
		rui_A[0]=1ull;
		rui_B[0]=1ull;
		for(int i=1;i<ps;i++)
		{
			rui_A[i]=mul_(rui_A[i-1],A);
			rui_B[i]=mul_(rui_B[i-1],B);
		}
		hash_A[0]=p[0];
		hash_B[0]=p[0];
		for(int i=1;i<ps;i++)
		{
			hash_A[i]=plus_(hash_A[i-1],mul_(p[i],rui_A[i]));
			hash_B[i]=plus_(hash_B[i-1],mul_(p[i],rui_B[i]));
		}
	}
	bool check(int x) 
	// this function checks if p[0...ps-1-x] == p[x...ps-1]
	// Image:
	// [..............]
	//        [...............]
	// <- x ->
	//        | same? |
	{
		if(x>=ps)return true;// not overlap
		/* debug
		cout << hash_A[ps-1-x] << ' ' << rui_A[x] << endl;
		cout << hash_A[ps-1] << ' ' << hash_A[x-1] << endl;
		cout << hash_A[ps-1-x]*rui_A[x] << ' ' << hash_A[ps-1]-hash_A[x-1] << endl;
		cout << hash_B[ps-1-x]*rui_B[x] << ' ' << hash_B[ps-1]-hash_B[x-1] << endl;
		*/
		if(!(mul_(hash_A[ps-1-x],rui_A[x])==minus_(hash_A[ps-1],hash_A[x-1])))return false;
		if(!(mul_(hash_B[ps-1-x],rui_B[x])==minus_(hash_B[ps-1],hash_B[x-1])))return false;
		return true;
	}
};
int main()
{
	string s;
	cin >> s;
	Rolling_hash Rh(s);
	return 0;
}
