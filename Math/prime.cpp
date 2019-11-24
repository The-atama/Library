#include <cstdio>
using namespace std;
#define MAX_N 2000000
//配列は必ずMAX+Nより大きくとること!!!!!(配列外参照)
int prime[MAX_N+100];
void eratos()
{
    for(int i=0;i<MAX_N;i++)prime[i]=1;
    prime[0]=prime[1]=0;
    for(int i=2;i*i<=MAX_N;i++)if(prime[i])
    {
        for(int j=i*2;j<=MAX_N;j+=i)prime[j]=0;
    }
    return;
}
int main()
{
    eratos();
	int cnt = 0;
	for(int i=0;i<MAX_N;i++)if(prime[i])cnt++,printf("%d\n",i);
	printf("%d\n",cnt);
    return 0;
}
