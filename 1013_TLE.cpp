// 非常简洁的代码，但是却TLE了，可见对于大数而言，求余很费事，不如逐位加减来得快
#include<cstdio>
#include<iostream>

using namespace std;

int main(){
    int i,sum;
    cin>>sum;
    while(sum){
        cout<<(sum-1)%9+1<<endl;
        cin>>sum;
    }
}
