#include<iostream>
//显示是否所有数组在前50对数据里面都能找到循环序列
using namespace std;
int main()
{
    char appear[7][7]={};
    int data[51]={};
    data[0]=data[1]=1;
    for(int a=0;a<7;++a){
        for(int b=0;b<7;++b){
            for(int i=2;i<51;++i){
                data[i]=(a*data[i-1]+b*data[i-2])%7;
                for(int j=0;j<i-1;++j)if(data[j]==data[i-1]&&data[j+1]==data[i]){
                    appear[a][b]=1;
                    break;
                }
                if(appear[a][b])break;
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
