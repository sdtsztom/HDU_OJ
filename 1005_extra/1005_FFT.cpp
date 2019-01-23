/*
 *矩阵快速幂做法，答案来自网上，放在这里用作参考
 */
#include<cstdio>
#include<iostream>
using namespace std;
int juzhen[2][2],final[2][2];
void jzcf1()
{
  int res[2][2]; 
  res[0][0]=(juzhen[0][0]*final[0][0]+juzhen[0][1]*final[1][0])%7;
  res[0][1]=(juzhen[0][0]*final[0][1]+juzhen[0][1]*final[1][1])%7;
  res[1][0]=(juzhen[1][0]*final[0][0]+juzhen[1][1]*final[1][0])%7;
  res[1][1]=(juzhen[1][0]*final[0][1]+juzhen[1][1]*final[1][1])%7;
  for(int i=0;i<=1;i++)
    for(int j=0;j<=1;j++)
      juzhen[i][j]=res[i][j]; 
}
void jzcf2()
{
  int res[2][2];
  res[0][0]=(final[0][0]*final[0][0]+final[0][1]*final[1][0])%7;
  res[0][1]=(final[0][0]*final[0][1]+final[0][1]*final[1][1])%7;
  res[1][0]=(final[1][0]*final[0][0]+final[1][1]*final[1][0])%7;
  res[1][1]=(final[1][0]*final[0][1]+final[1][1]*final[1][1])%7;
  for(int i=0;i<=1;i++)
    for(int j=0;j<=1;j++)
      final[i][j]=res[i][j]; 
}
int main()
{
  int flag=1;
  while(flag)
  {
    int a,b;
    int ans;
    long long int n;
    scanf("%d%d%lld",&a,&b,&n); 
    if(a || b || n)
    {
      final[0][0]=a;
      final[0][1]=b;
      final[1][0]=1;
      final[1][1]=0;
      juzhen[0][0]=1;
      juzhen[0][1]=0;
      juzhen[1][0]=0;
      juzhen[1][1]=1;
      if(n>=3)
      {
        n-=2;
        while(n)    //矩阵快速幂 
        {
          if(n&1)
          {
            jzcf1();
          }
          jzcf2();
          n >>= 1;
        }
        ans=(juzhen[0][0]+juzhen[0][1])%7;//此处应为final[0][0]*f(2)+final[0][1]*f(1)
        cout << ans << endl; 
      }
      else
        cout << "1" << endl;  //n=1,2时不妨直接输出1 
    }
    else
      flag=0;
  }
  return 0;
}