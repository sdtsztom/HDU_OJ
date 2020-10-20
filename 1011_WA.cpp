#include <cstdio>
#include<iostream>
#include<cmath>
using namespace std;

int n,m;
int roomDes[101][2];
short edges[100][2];
int maxPos=0;

void calPosi(int father,int self,int mleft,int posi);

int main(void)
{

    int i;
    while(true){
        cin>>n>>m;
        if(n==-1&&m==-1)break;
        maxPos=0;
        for(i=1;i<n+1;++i)scanf("%d %d",&roomDes[i][0],&roomDes[i][1]);
        for(i=0;i<n-1;++i)scanf("%d %d",&edges[i][0],&edges[i][1]);

        // cal room1
        calPosi(0,1,m,0);
        cout<<maxPos<<endl;
    }
}

void calPosi(int father,int self,int mleft,int posi){
    int myPosi=posi;
    int myMleft=mleft;
    int i;
    myMleft-=ceil(roomDes[self][0]/20);
    if(myMleft<0)return;
    myPosi+=roomDes[self][1];
    if(myPosi>maxPos)maxPos=myPosi;
    for(i=0;i<n-1;++i){
        if(edges[i][0]==self&&edges[i][1]!=father)calPosi(self,edges[i][1],myMleft,myPosi);
        else if(edges[i][1]==self&&edges[i][0]!=father)calPosi(self,edges[i][0],myMleft,myPosi);
    }
}
