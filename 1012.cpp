#include<cstdio>
#include<iostream>

using namespace std;

double sum;
int fac;

int main(){
    int i;
    cout<<"n e"<<endl;
    cout<<"- -----------"<<endl;
    sum=1;
    fac=1;
    cout<<"0 1"<<endl;
    for(i=1;i<10;++i){
        fac*=i;
        sum=1.0/fac+sum;
        if(i==1)printf("%d %.0f\n",i,sum);
        else if(i==2)printf("%d %.1f\n",i,sum);
        else printf("%d %.9f\n",i,sum);
    }
	return 0;
}
