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
struct cards
{
    int from,to;
    cards(int f,int t)
    {
        from=f,to=t;
    }
};
deque<cards> all;
deque<cards> split(int k)//上からx枚と残りに分割
{
    deque<cards> sub;
    if(k==0)return sub;
    if(k<0)
    {
    	cout << "ERROR" << endl;
    	return sub;
    }
    for(;;)
    {
        cards t=all.front();
        all.pop_front();
        k -= t.to-t.from+1;
        if(k==0)
        {
            sub.pb(t);
            break;
        }
        if(k<0)
        {
            all.push_front(cards(t.to+k+1,t.to));
            t.to+=k;
            sub.pb(t);
            break;
        }
        sub.pb(t);
    }
    return sub;
}
//シャッフルの仕方で適宜変更
//push_frontする時は逆向きにすることに注意
void shuffle(int x,int y)
{
    deque<cards> a=split(x);
    deque<cards> b=split(y-x);
    for(int i=0;i<b.size();i++)all.pb(b[i]);
    for(int i=0;i<a.size();i++)all.pb(a[i]);
}
int main()
{
	int n,m,p,q,r;
    while(1)
    {
        cin >> n;
        if(n==0)break;
        all.clear();
        all.pb(cards(1,n));
        cin >> m;
        cin >> p >> q >> r;
        for(int i=0;i<m;i++)
        {
            int x,y;
            cin >> x >> y;
            shuffle(x,y);
        }
        //AOJ 0536
        /*int ans=0;
        split(p-1);
        deque<cards> res=split(q-p+1);
        for(int i=0;i<res.size();i++)
        {
            if(res[i].from<=r)
            {
                if(res[i].to>=r)
                {
                    ans+=r-res[i].from+1;
                }
                else
                {
                    ans+=res[i].to-res[i].from+1;
                }
            }
        }
        cout << ans << endl;*/
    }
    return 0;
}
