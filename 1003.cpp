//此题做不来，直接参考网上答案
#include <iostream>
using namespace std;
 
int main()
{
	int j;
	int n,m;
	int s=0;
	int temp=0;
	int start,end;
	int max=-1001;
	int sum=0;
	int q=1;
	cin>>n;
	while(n--)
	{
		sum=0;
		temp=0;
		max=-1001;
		s=0;
		cin>>m;
		while(m--)
		{
			cin>>j;
			sum+=j;
			if(sum>max)
			{
				max=sum;
				start=s;
				end=s+temp;
			}
			temp++;
			if(sum<0)
			{
				sum=0;
				s=s+temp;
				temp=0;
			}
		}
		if(q!=1)
			cout<<endl;
		cout<<"Case "<<q++<<":"<<endl;
		cout<<max<<' '<<start+1<<' '<<end+1<<endl;;
	}
}