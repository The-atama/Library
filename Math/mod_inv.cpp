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
#define MOD 1000000007 // prime
const int SIZE = 100100;
ll inv[SIZE+10],fac[SIZE+10],facinv[SIZE+10];
//size of arrays should be bigger than SIZE !!
ll nCr(int n,int r)
{
	if(n<r)return -1ll;
	if(n<0||r<0)return -1ll;
	if(n==0&&r==0)return 1ll;
	return ((fac[n]*facinv[r]%MOD)*facinv[n-r])%MOD;
}
int main()
{
	fac[0]=1ll;
	for(int i=1;i<=SIZE;i++)fac[i]=(fac[i-1]*i)%MOD;
	inv[1]=1ll;
	for(int i=2;i<=SIZE;i++)inv[i]=((-(MOD/i)*inv[MOD%i])%MOD+MOD)%MOD;
	facinv[0]=1ll;
	for(int i=1;i<=SIZE;i++)facinv[i]=(facinv[i-1]*inv[i])%MOD;
	return 0;
}
