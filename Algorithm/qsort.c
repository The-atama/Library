#include <stdio.h>
void qsort(int a[],int left,int right)
{
	if(left < right)
	{
		int pvot,tmp,i,j;
		i = left;
		j = right;
		pvot = (a[i] + a[j])/2;
		while(1)
		{
			while(a[i] < pvot)i++;
			while(a[j] > pvot)j--;
			if(i >= j)
			{
				break;
			}
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			i++;
			j--;
		}
		qsort(a,left,i -1);
		qsort(a,j + 1,right);
	}
	return;
}
int main(void)
{
	int i,n;
	int array[100];
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&array[i]);
	}
	qsort(array,0,n-1);
	for(i = 0;i < n-1;i++)
	{
		printf("%d ",array[i]);
	}
	printf("%d\n",array[n-1]);
	return 0;
}
