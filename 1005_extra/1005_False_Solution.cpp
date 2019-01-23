/*
 * 这是网上流传的错误代码
 */
 
#include<iostream>
using namespace std;
int main()
{
    int f[110];
    int a,b,n,i;
    f[1]=f[2]=1;
    while(1){
        cin>>a>>b>>n;
        if(!(a||b||n))break;
        if(n>2){
            for(i=3;i<100;++i){
                f[i]=(a*f[i-1]+b*f[i-2])%7;
                if(f[i]==1&&f[i-1]==1)break;
            }
            i=i-2;
            n=n%i;
            if(n==0)n=i;
            cout<<f[n]<<endl;
        }else cout<<1<<endl;
    }
	return 0;
}
