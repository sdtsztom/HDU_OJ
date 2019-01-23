#include<iostream>
using namespace std;
int main()
{
    int a,b,n,i;
    int f1,f2,f3;
    while(1){
        cin>>a>>b>>n;
        if(!(a||b||n))break;
        f1=f2=1;
        if(n>2){
            for(i=2;i<n;++i){
                f3=(a*f2+b*f1)%7;
                f1=f2;
                f2=f3;
            }
            cout<<f3<<endl;
        }else cout<<1<<endl;
    }
    return 0;
}
