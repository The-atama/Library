#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
struct Int
{
	int digit[50];
	Int()
	{
		memset(digit,0,sizeof(digit));
	}
	void add(Int b)
	{
		int k=0;
		for(int i=0;i<50;i++)
		{
			int p=k+digit[i]+b.digit[i];
			if(p>=10)k=1;
			else k=0;
			digit[i]=p%10;
		}
		return;
	}
	void set(string s)
	{
		for(int i=0;i<s.size();i++)digit[i]=s[s.size()-1-i]-'0';
		return;
	}
	void print()
	{
		int p=49;
		while(digit[p]==0)p--;
		for(int i=p;i>=0;i--)printf("%d",digit[i]);
		puts("");
		return;
	}
};
int main()
{
	string a,b;
	cin >> a >> b;
	Int A,B;
	A.set(a);
	B.set(b);
	A.add(B);//A+=B
	A.print();
	return 0;
}
