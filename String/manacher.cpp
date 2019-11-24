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
int Manacher(const string &_s)//return longest palindrome's length.
{
	int n=_s.size(),i,j;
	string s(2*n+1,'$');
	for(int i=0;i<n;i++)s[2*i+1]=_s[i];
	n=2*n+1;
	vector<int> rad(n);
	for(i=j=0;i<n;)
	{
		while(0<=i-j&&i+j<n&&s[i-j]==s[i+j])j++;
		rad[i]=j;
		int k;
		for(k=1;i-k>=0&&rad[i-k]<rad[i]-k;k++)rad[i+k]=rad[i-k];
		i+=k;
		j=max(j-k,0);
	}
	return *max_element(rad.begin(),rad.end())-1;
}
int main()
{
	string s;
	cin >> s;
	cout << Manacher(s) << endl;
	return 0;
}
