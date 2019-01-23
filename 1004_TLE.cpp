#include <iostream>
#include <string>
using namespace std;

typedef struct _Color{
    string color;
    int cnt;
    struct _Color *next;
    struct _Color *true_next;
}Color;

Color *head=NULL;
Color *end_present=NULL;

int main()
{
	int n=0;
	Color *a[26]={};
	Color *p1,*p2;
	string color_name;
	int max_cnt=0;
	Color *max_color=NULL;

	while(cin>>n&&n){
        head=end_present=NULL;
        max_cnt=0;
        Color *max_color=NULL;
        while(n--){
            cin>>color_name;
            p1=a[color_name[0]-97];
            p2=p1;
            while(p1){  //p1!=NULL => not empty row
                if(p1->color==color_name){
                    p1->cnt+=1;
                    break;
                }else {
                    p2=p1;
                    p1=p1->next;
                }
            }
            if(!p1){ //p==NULL => color_name not exist
                Color *clr=new Color{color_name,1,NULL,NULL};
                if(!p2)a[color_name[0]-97]=clr; //p2=NULL => empty row
                else p2->next=clr;
                if(!head)head=end_present=clr;  //head==NULL => global empty
                else{
                    end_present->true_next=clr;
                    end_present=clr;
                }
            }
        }
        //get max
        p1=head;
        while(p1){
            if(p1->cnt>max_cnt){
                max_cnt=p1->cnt;
                max_color=p1;
            }
            p1=p1->true_next;
        }
        cout<<max_color->color<<endl;
        //free memory
        p1=head;
        p2=head->true_next;
        while(p1){
            delete p1;
            p1=p2;
            if(p2)p2=p2->true_next;
        }
	}
	return 0;
}
