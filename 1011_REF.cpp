#include<set> 
#include<map>
#include<stack>
#include<cmath>
#include<queue>
#include<vector>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>
#define rep(i,a,b) for(i=a;i<=b;i++)
#define rec(i,a)   for(i=0;i< a;i++)
#define N 10000  +  10
#define Q 1000   +  10
#define P 100    +  1
#define value VALUE
#define cost COST
#define need NEED
using namespace std;
int n,m; 
vector<int>G[P];
int cost[P]={0};
int value[P]={0};
int mark[P]={0}; //记录当前节点有无被搜索过
int dp[P][P]={0}; // 设dp[i][j]是在根节点为i,使用了j个士兵，我们能获得的最大收益。由于1是入口，那么1是根 
void dfs(int u){
	mark[u]=1;
	int need = (cost[u]+19)/20;	//ceil的意思
	for(int i=need;i<=m;i++)dp[u][i]=value[u]; //在当前根，至少要用need个人，最多不能用超过m个人，此时都只能获得当前房间的收益 value[u]
	for(int i=0;i<G[u].size();i++){	//u:当前节点;
									//v:子节点;
									//j:为当u节点和之前搜寻过的u的子节点分配j个士兵;
									//k:为当前子节点v分配k个士兵
		int v=G[u][i];
		if(mark[v]==0){
			dfs(v);
			for(int j=m-1;j>=need;j--){	//在dfs子节点后更新当前节点的最优信息
				for(int k=1;k+j<=m;k++)	//note: k=1决定了即使子节点的need为0也会派一个人过去
				dp[u][j+k]=max(dp[u][j+k],dp[u][j]+dp[v][k]);//在节点u，与和u相连的点v，一共可用j个人，分派k个人到v上，而且两个点分派的人数之和不能超过m。dp[u][j+k]取较大的值 
			}
		} 
	} 
}
int main(){
	int i,j;
	int x,y;
	while(scanf("%d%d",&n,&m)==2){
		if(n==-1&&m==-1)break;
		for(i=0;i<P;i++)G[i].clear();memset(dp,0,sizeof dp);memset(mark,0,sizeof mark);memset(cost,0,sizeof cost);memset(value,0,sizeof value);	//数据初始化
		for(i=1;i<=n;i++)scanf("%d%d",&cost[i],&value[i]);
		for(i=1;i< n;i++){scanf("%d%d",&x,&y);G[x].push_back(y);G[y].push_back(x);}	//建立邻接表
		if(m==0){printf("0\n");continue;}
		dfs(1);
		printf("%d\n",dp[1][m]);
	}
return 0;
}