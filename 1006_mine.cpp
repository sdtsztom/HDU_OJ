#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

typedef struct Section{
	double ceiling;
	double floor;
}section;

int i_sAh,i_sAm,i_mAh;	// pointer

double D;

double percentage=0;
double total_time=0;    //unit:min

double m2h=5.5;	//volocity of minute hand relative to hour hand,unit:/min
double s2h=359.5;	//volocity of second hand relative to hour hand,unit:/min
double s2m=354;	//volocity of second hand relative to minute hand,unit:/min

section mAh;	//totally update 11 times(including init)
section sAh;	//totally update 719 times(including init)
section sAm;	//totally update 708 times(including init)
section u;

double interval_mAh=360/m2h;
double interval_sAh=360/s2h;
double interval_sAm=360/s2m;

section union_section(section& mAh,section& sAh,section& sAm);
double time_of_section(section& a);
void init_section(section& mAh,section& sAh,section& sAm);
void update_section_sAm(section& sAm);
void update_section_sAh(section& sAh);
void update_section_mAh(section& mAh);

int main(){
	while(cin>>D&&D!=-1){
		if(D==120)percentage=0;
		else if(D==0)percentage=100;
		else{
            i_sAh=i_sAm=i_mAh=1;
            init_section(mAh,sAh,sAm);
            total_time=0;
			while(1){		//(i_sAh<720&&i_sAm<709&&i_mAh<12)
                u=union_section(mAh,sAh,sAm);
				if(u.floor>720)break;
                total_time+=time_of_section(u);
			}
			percentage=total_time/720*100;
		}
		cout<<setprecision(3)<<fixed<<percentage<<endl;
	}
}

section union_section(section& mAh,section& sAh,section& sAm){
    section s;
    double min_max,max_min;
	do{
        min_max=min(min(mAh.ceiling,sAm.ceiling),min(sAm.ceiling,sAh.ceiling));
        max_min=max(max(mAh.floor,sAm.floor),max(sAm.floor,sAh.floor));
        if(min_max==mAh.ceiling){
            i_mAh+=1;
            update_section_mAh(mAh);
        }else if(min_max==sAm.ceiling){
            i_sAm+=1;
            update_section_sAm(sAm);
        }else{
            i_sAh+=1;
            update_section_sAh(sAh);
        }
	}while(min_max<=max_min);
	s.ceiling=min_max;
	s.floor=max_min;
	return s;
}

double time_of_section(section& a){
	return a.ceiling-a.floor;
}

void init_section(section& mAh,section& sAh,section& sAm){
	mAh.floor=D/m2h;
	mAh.ceiling=(360-D)/m2h;
	sAh.floor=D/s2h;
	sAh.ceiling=(360-D)/s2h;
	sAm.floor=D/s2m;
	sAm.ceiling=(360-D)/s2m;
}

void update_section_sAm(section& sAm){
    //approximately,for a better speed
	sAm.floor+=interval_sAm;
	sAm.ceiling+=interval_sAm;
//    sAm.floor=((i_sAm-1)*360+D)/s2m;
//    sAm.ceiling=(i_sAm*360-D)/s2m;
}

void update_section_sAh(section& sAh){
    //approximately,for a better speed
	sAh.floor+=interval_sAh;
	sAh.ceiling+=interval_sAh;
//    sAh.floor=((i_sAh-1)*360+D)/s2h;
//    sAh.ceiling=(i_sAh*360-D)/s2h;
}

void update_section_mAh(section& mAh){
    //approximately,for a better speed
	mAh.floor+=interval_mAh;
	mAh.ceiling+=interval_mAh;
//    mAh.floor=((i_mAh-1)*360+D)/m2h;
//    mAh.ceiling=(i_mAh*360-D)/m2h;
}
