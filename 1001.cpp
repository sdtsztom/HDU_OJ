/*
 *官方坑：注意输出两个换行符
 */
 
#include<iostream>

using namespace std;
int main(){
	int a;
	while(cin>>a){
		if(a%2==0)cout<<a/2*(1+a)<<endl<<endl;
		else cout<<(a+1)/2*a<<endl<<endl;
	}
	return 0;
}