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
bool c[300010];
int a[300010];
int N,Q,maxc=-1,ans=0;
int s[300010];
int main()
{
    cin >> N >> Q;
    for(int i=0;i<N;i++)
    {
        cin >> a[i];
        maxc=max(maxc,a[i]);
        c[a[i]]=true;
    }
    for(int i=0;i<=maxc;i++)
    {
        if(c[i])s[i+1]=i;
        else s[i+1]=s[i];
    }
    for(int i=0;i<Q;i++)
    {
        int q;
        cin >> q;
        ans=0;
        for(int d=maxc;;)
        {
            int p=d%q;
            ans=max(ans,p);
            if(d-p<=0)break;
            d=s[d-p];
        }
        cout << ans << endl;
    }
    return 0;
}
