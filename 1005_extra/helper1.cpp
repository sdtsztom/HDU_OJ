#include<iostream>
//print f(n)
using namespace std;
int main()
{
    int a,b,i;
    int f1,f2,f3;
    int f[20];
    char co='y';
    bool first=true;
    cin>>a>>b;
    f1=f2=1;
    while(1){
        if(co=='q')break;
        if(first){
            i=18;
            f[0]=f1;
            f[1]=f2;
            first=false;
        }else i=20;
        while(i--){
            f3=(a*f2+b*f1)%7;
            f1=f2;
            f2=f3;
            f[19-i]=f3;
        }
        for(int k=0;k<2;++k){
            for(int j=0;j<10;++j)cout<<f[k*10+j]<<' ';
            cout<<endl;
        }
        cin>>co;
    }
    return 0;
}
