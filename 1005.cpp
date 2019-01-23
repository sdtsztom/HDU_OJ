#include<iostream>
using namespace std;
int main()
{
    int appear[7][7]={};
    int t[7][7]={};
    int data[51]={};
    int a,b,n;
    int appear_i,t_i;
    int extra;

    data[0]=data[1]=1;

    for(a=0;a<7;++a){
        for(b=0;b<7;++b){
            for(int i=2;i<51;++i){
                data[i]=(a*data[i-1]+b*data[i-2])%7;
                for(int j=0;j<i-1;++j)if(data[j]==data[i-1]&&data[j+1]==data[i]){
                    appear[a][b]=j;
                    t[a][b]=i-1-j;
                    break;
                }
                if(t[a][b])break;
            }
        }
    }

    while(1){
        cin>>a>>b>>n;
        if(!(a||b||n))break;
        a%=7;
        b%=7;
        if(n>2){
            appear_i=appear[a][b];
            t_i=t[a][b];
            for(int i=2;i<appear_i+t_i;++i)data[i]=(a*data[i-1]+b*data[i-2])%7;
            extra=(n-appear_i)%t_i;
            if(!extra)extra=t_i;
            cout<<data[appear_i-1+extra]<<endl;
        }else cout<<1<<endl;
    }

    return 0;
}
