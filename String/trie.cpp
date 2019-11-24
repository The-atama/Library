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
#define EQ(a,b) (abs((a)-(b))<eps)
struct Trie{
	int child_num;
	Trie *child[26];
	bool flag;//sokode kakutei suruka
	Trie(){
		child_num = 0;
		flag = true;
		for(int i=0;i<26;i++)child[i]=(Trie *)NULL;
	}
};
Trie *root;
int find(string s,Trie *ptr)
{
	for(int i=0;i<s.size();i++)
	{
		int idx = s[i]-'a';
		ptr = ptr->child[idx];
		if(ptr->flag)return i+1;
	}
	return (int)s.size();
}
void update(string s,Trie *ptr)
{
	for(int i=0;i<s.size();i++)
	{
		int idx = s[i]-'a';
		if(!(ptr->child[idx]))
		{
			(ptr->child_num)++;
			ptr->child[idx] = new Trie();
		}
		else ((ptr->child[idx])->flag)=false;
		ptr = ptr->child[idx];
	}
	return;
}
int main()
{
	int T;
	scanf("%d",&T);
	for(int t=0;t<T;t++)
	{
		int N,ans=0;
		scanf("%d",&N);
		root = new Trie();
		for(int i=0;i<N;i++)
		{
			string s;
			cin >> s;
			update(s,root);
			//cout << find(s,root) << endl;
			ans += find(s,root);
		}
		printf("Case #%d: %d\n",t+1,ans);
		delete root;
	}
	return 0;
}
