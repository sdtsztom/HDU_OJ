#include<iostream>
#include<string>

using namespace std;

int main(){
    int n,b[1000],cnt_max=0;
    string a_max;
    string a[1000];
    while(cin>>n && n){
        cnt_max=0;

        for(int i=0;i<n;++i)cin>>a[i];

        for(int i=0;i<n;++i){
            b[i]=1;
            for(int j=i+1;j<n;++j)if(a[i]==a[j])++b[i];

            if(b[i]>cnt_max){
                cnt_max=b[i];
                a_max=a[i];
            }
        }
        cout<<a_max<<endl;
    }
    return 0;
}
