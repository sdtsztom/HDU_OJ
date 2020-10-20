// 利用了余九算法，效率大大提高
#include<cstdio>
#include<iostream>
#include<string>

using namespace std;

int main(){
    int i,sum;
    string s;
    cin>>s;
    while(s!="0"){
        sum=0;
        for(i=0;i<s.size();++i)sum+=s[i]-'0';
        cout<<(sum-1)%9+1<<endl;
        cin>>s;
    }
}
