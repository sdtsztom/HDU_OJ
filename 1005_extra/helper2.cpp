#include<iostream>
//显示是否所有情况下都有11开头的循环序列
using namespace std;
int main()
{
    char appear[7][7]={};
    int data[51]={};
    for(int a=0;a<7;++a){
        for(int b=0;b<7;++b){
            data[0]=data[1]=1;
            for(int i=2;i<51;++i){
                data[i]=(a*data[i-1]+b*data[i-2])%7;
                if(data[i]==1&&data[i-1]==1){
                    appear[a][b]=1;
                    break;
                }
            }
        }
    }

    for(int a=0;a<7;++a){
        for(int b=0;b<7;++b){
            cout<<(int)appear[a][b]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
