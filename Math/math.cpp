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
#define MAX 100000
vector<ll> divisor;
bool isprime[MAX];
vector<ll> prime;
void eratos()
{
	memset(isprime,true,sizeof(isprime));
	for(int i=3;i*i<MAX;i++)
	{
		if((i&1)&&isprime[i])
		{
			for(int j=i*2;j<MAX;j+=i)
			{
				isprime[j]=false;
			}
		}
	}
	prime.pb(2ll);
	for(ll i=3ll;i<MAX;i+=2ll)
	{
		if(isprime[(int)i])prime.pb(i);
	}
	return;
}
ll mul(ll a,ll b,ll mod)
{
	if(b==0ll)return 0ll;
	ll res=mul((a+a)%mod,b/2ll,mod);
	if(b&1)res=(res+a)%mod;
	return res;
}
ll pow(ll x,ll a,ll mod)
{
	if(a==0ll)return 1ll;
	ll res=pow(mul(x,x,mod),a/2ll,mod);
	if(a&1)res=mul(res,x,mod);
	return res;
}
inline ll my_rand(ll x,ll c,ll mod)
{
	return (mul(x,x,mod)+c)%mod;
}
bool miller_rabin(ll n)
{
	if(n==2ll)return true;
	if((n&1)==0||n<=1)return false;
	int a[10]={2,3,5,7,11,13,17,19,23,-1};
	ll s=0ll,d,x,r;
	d=n-1;
	while((d&1)==0)s++,d>>=1;
	for(int i=0;a[i]!=-1&&a[i]<n;i++)
	{
		if((x=pow(a[i],d,n))!=1ll)
		{
			for(r=0ll;r<s;r++)
			{
				if(x==n-1ll)break;
				x=mul(x,x,n);
			}
			if(r==s)return false;
		}
	}
	return true;
}
void first(ll n)
{
	for(int i=0;i<prime.size();i++)
	{
		bool k=false;
		while(n%prime[i]==0)
		{
			if(!k)
			{
				divisor.pb(prime[i]);
				k=true;
			}
			n/=prime[i];
		}
	}
	return;
}
void pollards_rho(ll n)
{
	if(n==1ll)return;
	if(miller_rabin(n))
	{
		divisor.pb(n);
		return;
	}
	ll x=2,y=2,d=1;
	while(d==1)
	{
		x=my_rand(x,1,n);
		y=my_rand(my_rand(y,1,n),1,n);
		d=__gcd(llabs(x-y),n);
	}
	if(d==n)return;
	pollards_rho(d);
	pollards_rho(n/d);
}
int main()
{
	int n;
	scanf("%d",&n);
	eratos();
	for(int i=0;i<n;i++)
	{
		divisor.clear();
		ll x;
		scanf("%lld",&x);
		if(miller_rabin(x))
		{
			printf("Prime\n");
		}
		else
		{
			first(x);
			pollards_rho(x);
			SORT(divisor);
			printf("%lld\n",divisor[0]);
		}
	}
	return 0;
}
