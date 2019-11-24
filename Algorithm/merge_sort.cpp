#include <stdio.h>
#include <string.h>
#define INF 200000000
int n,size=1;
int a[2000100],tmp[2000100];
void merge(int left,int mid,int right)
{
	for(int i=left;i<=right;i++)tmp[i]=0;
	int index=left;
	int l=left,m=mid;
	while(l<mid&&m<right)
	{
		if(a[l]<a[m])tmp[index++]=a[l++];
		else tmp[index++]=a[m++];
	}
	while(l<mid)tmp[index++]=a[l++];
	while(m<right)tmp[index++]=a[m++];
	for(int i=left;i<index;i++)a[i]=tmp[i];
	return;
}
void merge_sort(int left,int right)
{
	if(right-left==1)return;
	int mid=(left+right)/2;
	merge_sort(left,mid);
	merge_sort(mid,right);
	merge(left,mid,right);
	return;
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	while(size<n)size*=2;
	for(int i=n;i<size;i++)a[i]=INF;
	merge_sort(0,size);
	for(int i=0;i<n;i++)
	{
		if(i<n-1)printf("%d ",a[i]);
		else printf("%d\n",a[i]);
	}
	return 0;
}
