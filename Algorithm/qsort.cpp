#include <cstdio>
#include <algorithm>
using namespace std;
int a[1000100];
int n;
void qsort(int left,int right)
{
	if(left>=right)return;
	int pivot=(a[left]+a[right])/2;
	int l=left,r=right;
	while(1)
	{
		while(a[l]<pivot)l++;
		while(a[r]>pivot)r--;
		if(r<=l)break;
		swap(a[l],a[r]);
		l++;
		r--;
	}
	qsort(left,l-1);
	qsort(r+1,right);
	return;
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	qsort(0,n-1);
	for(int i=0;i<n;i++)
	{
		if(i<n-1)printf("%d ",a[i]);
		else printf("%d\n",a[i]);
	}
	return 0;
}
