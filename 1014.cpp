//欧几里得算法
#include<cstdio>
#include<iostream>
#include<iomanip>

using namespace std;

int main(){
    int mod,step;
    int m,n,r;
    int flag_prime;
    string judge="";
    while(scanf("%d %d",&step,&mod)==2){
        m=mod;n=step;
        if(m<n){r=m;m=n;n=r;}   // swap,make m>=n
        do{r=m%n;m=n;n=r;}while(r);
        if(m==1){
            flag_prime=1;
            judge="Good Choice";
        }else{
            flag_prime=0;
            judge="Bad Choice";
        }
        cout<<setw(10)<<step<<setw(10)<<mod<<"    "<<judge<<endl<<endl;
    }
}
