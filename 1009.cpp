/*
 * 坑题，用c++式输出(保留3位小数)会wa
 */
 
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<iomanip>

#define INF 10000

using namespace std;

typedef struct{
    int J;
    int F;
    double cost;
}Room;

int compare(const void *a,const void *b);

int main(){
    int m,n;
    Room r[1000];
    double gain;
    int i=0;
	while(1){
        cin>>m>>n;
        if(m==-1&&n==-1)break;
        for(i=0;i<n;++i)cin>>r[i].J>>r[i].F;
        for(i=0;i<n;++i){
            if(r[i].F!=0)r[i].cost=(double)r[i].J/r[i].F;
            else r[i].cost=INF;
        }
        qsort(r,n,sizeof(Room),compare);
        gain=i=0;
        while(m>0&&i<n){
            if(r[i].F<=m){
                gain+=r[i].J;
                m-=r[i].F;
                ++i;
            }else{
                gain+=m*r[i].cost;
                m=0;
            }
        }
        // cout<<fixed<<setprecision(3)<<gain<<endl;
        printf("%.3f\n",gain);
	}
	return 0;
}

int compare(const void *a,const void *b){return ((Room*)b)->cost>((Room*)a)->cost?1:-1;}
