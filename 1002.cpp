/*
 *官方坑：最后一次不用输出两个换行符
 */

#include<iostream>
#include<cstring>
using namespace std;

int add(char*a,char*b,char*sum);

int main(){
    char a[1001],b[1001],sum[1001];
	int len,i;
	int carry_bit=0;

	cin>>len;

	for(i=1;i<len+1;++i){
		cin>>a>>b;
		carry_bit=add(a,b,sum);
		cout<<"Case "<<i<<':'<<endl;
		cout<<a<<" + "<<b<<" = ";
		if(carry_bit)cout<<'1';
		cout<<sum<<endl;
		if(i<len)cout<<endl;
	}
	return 0;
}

int add(char* a,char* b,char* sum){
	int len_a,len_b,len_min,len_max;
	char* a_min,*a_max;
	int carry_bit=0;
	int i,j;

	len_a=strlen(a);
	len_b=strlen(b);
	if(len_a>len_b){
		a_max=a;
		a_min=b;
		len_max=len_a;
		len_min=len_b;
	}else{
		a_max=b;
		a_min=a;
		len_max=len_b;
		len_min=len_a;
	}

	sum[len_max]=0;
	for(i=len_min-1,j=len_max-1;i>-1;--i,--j){
		sum[j]=a_min[i]+a_max[j]+carry_bit-48;
		if(sum[j]>57){
			sum[j]-=10;
			carry_bit=1;
		}else carry_bit=0;
	}

	while(j>-1){
		sum[j]=a_max[j]+carry_bit;
		if(sum[j]>57){
			sum[j]-=10;
			carry_bit=1;
		}else carry_bit=0;
		--j;
	}
	return carry_bit;
}
