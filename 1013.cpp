// 第一次使用字符串来处理数字，接下来都使用数字来处理，依然能够AC
#include<cstdio>
#include<iostream>
#include<string>

using namespace std;

int digitSum(int i);

int main(){
    int i,sum;
    string s;
    cin>>s;
    while(s!="0"){
        sum=0;
        for(i=0;i<s.size();++i)sum+=s[i]-'0';
        while(sum>9)sum=digitSum(sum);
        cout<<sum<<endl;
        cin>>s;
    }
}

int digitSum(int i){
    int c,r,sum=0;
    do{
        sum+=i%10;
        i=i/10;
    }while(i);
    return sum;
}
