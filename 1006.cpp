#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std ;
struct Segment//区间结构
{
	double a,b;
};
//由两个区间求出它们的交区间
Segment operator *(Segment S1,Segment S2){
	Segment seg;
	seg.a=S1.a>S2.a?S1.a:S2.a;
	seg.b=S1.b<S2.b?S1.b:S2.b;
	if (seg.a>seg.b)
		seg.a=seg.b=0.0;
	return seg;
 
}
//“快乐时光”临界角度
double D;
//从D<=bS-a<=D1 中解出区间
Segment makeSeg1(double,double);
//从D<=a-bS<=D1
Segment makeSeg2(double,double);
 
int main(){  
	while (cin>>D,D!=-1)
	{
		double toLen=0.0;//“快乐时光”总长度
		//枚举时、分
		for (int H = 0; H < 12; H++)
		{
			for (int M = 0; M < 60; M++)
			{
				Segment S[3][2];
				//获得基本解区间
				double a,b;
				a=30.0*H-5.5*M;
				b=11.0/120;//时针-分针
				S[0][0]=makeSeg1(a,b);
				S[0][1]=makeSeg2(a,b);
				a=30.0*H+0.5*M;
				b=719.0/120;//秒针-时针
				S[1][0]=makeSeg1(a,b);
				S[1][1]=makeSeg2(a,b);
				a=6.0*M;
				b=5.9;//秒针-分针
				S[2][0]=makeSeg1(a,b);
				S[2][1]=makeSeg2(a,b);
				//将解集转化为区间的并，并累计“快乐时光”的长度
				for (int i = 0; i < 2; i++)
					for (int j = 0; j < 2; j++)
						for (int k = 0; k < 2; k++)
						{
							Segment TS=S[0][i]*S[1][j]*S[2][k];
							toLen+=TS.b-TS.a;
 
						}
 
			}
 
		}
		cout<<setprecision(3)<<fixed<< toLen / 432.0 <<endl;
	}
		system("pause");
        return 0;  
    }  
//从D<=bS-a<=D1中解出
Segment makeSeg1(double a,double b){
	Segment seg;
	seg.a=(D+a)/b,seg.b=(360.0-D+a)/b;
	if (seg.a<0.0) seg.a=0.0;
	if (seg.b>60.0)seg.b=60.0;
	if (seg.a>=seg.b)
		seg.a=seg.b=0.0;
	return seg;
}
//从D<=a-bS<=D1中解出区间
Segment makeSeg2(double a,double b){
	Segment seg;
	seg.a=(a+D-360.0)/b,seg.b=(a-D)/b;
	if (seg.a<0.0)
		seg.a=0.0;
	if (seg.b>60.0)
		seg.b=60.0;
	if (seg.a>=seg.b)
		seg.a=seg.b=0.0;
	return seg;
}
