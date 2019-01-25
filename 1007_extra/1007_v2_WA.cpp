/*
 * 为了解决malloc分配内存导致的TLE的问题，采用提前分配空间的方法
 * HDU OJ 提供了大约32mb的内存上限，这相当于28*10w个point的大小
 * 在MAXSIZE为10w的情况下，程序的递归大约会进行17层左右
 * 因此自己管理一个17*10w*sizeof(point)大小的空间来加快速度
 * 但是由于使用float导致submit后会出现Wrong Answer，而是用double又会导致内存不够用，因此还需要优化
 */

#include<iostream>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<string.h>
#include<cstdlib>

#define MAXSIZE 100000

using namespace std;

typedef struct {
	int index;
	float x;
	float y;
}point;

bool cmp_x(point p1, point p2);
bool cmp_y(point p1, point p2);
float find_min_dis(int low, int high, point X[], point Y[]);
float dis(point pt1, point pt2);
point * imalloc(int len);

point X[MAXSIZE];
point Y[MAXSIZE];
point Y_merge[MAXSIZE];
point pool[17 * MAXSIZE];
int pool_p = 0;

int main()
{
	int N;
	int i;
	while (cin >> N && N != 0) {
		//reset pool point
		pool_p = 0;

		// store data
		for (i = 0; i < N; ++i) {
			X[i].index=i;
			cin >> X[i].x;
			cin >> X[i].y;
		}

		memcpy(Y, X, N * sizeof(point));

		// presort
		sort(X, X + N, cmp_x);
		sort(Y, Y + N, cmp_y);

		float min_dis = find_min_dis(0, N - 1, X, Y);
		cout << fixed << setprecision(2)<< min_dis/2 << endl;
	}
}

bool cmp_x(point p1, point p2) { return p1.x < p2.x; }
bool cmp_y(point p1, point p2) { return p1.y < p2.y; }

float find_min_dis(int low, int high, point X[], point Y[]) {
	if (high - low == 1)return dis(X[high], X[low]);  //两个点
	else if (high - low == 2) {                       //三个点
		float dis1 = dis(X[high], X[high - 1]);
		float dis2 = dis(X[high], X[low]);
		float dis3 = dis(X[high - 1], X[low]);
		return min(min(dis1, dis2), dis3);
	}
	else {                                      // 三个点以上，需要分治
		int mid = (low + high) / 2;
		float mid_line = (X[mid].x + X[mid + 1].x) / 2;
		int len_left = mid - low + 1;
		int len_right = high - mid;
		point *Yl, *Yr;
		int nl = 0, nr = 0, n_merge = 0;
		int i, j;
		float min_dis, min_dis_left, min_dis_right, dis_temp;
		float delta;
		float left_bound, right_bound;

		Yl = imalloc(len_left);
		Yr = imalloc(len_right);

		//对Y中的点进行划分
		for (i = 0; i < high - low + 1; ++i) {
			if (Y[i].index <= mid) {
				Yl[nl++] = Y[i];
			}
			else Yr[nr++] = Y[i];
		}

		min_dis_left = find_min_dis(low, mid, X, Yl);
		min_dis_right = find_min_dis(mid + 1, high, X, Yr);
		delta = min(min_dis_left, min_dis_right);  //使用delta这个参数名是依据算法导论书中的命名
		left_bound = mid_line - delta;
		right_bound = mid_line + delta;

		//筛选出再S区域内的Y
		nl = nr = 0;
		//为了节省内存，直接在原数组上进行操作
		for (i = 0; i < len_left; ++i)if (Yl[i].x >= left_bound)Yl[nl++] = Yl[i];
		for (i = 0; i < len_right; ++i)if (Yr[i].x <= right_bound)Yr[nr++] = Yr[i];

		//合并所有的Y
		for (i = 0, j = 0; i < nl&&j < nr;) {
			if (Yl[i].y < Yr[j].y)Y_merge[n_merge++] = Yl[i++];
			else Y_merge[n_merge++] = Yr[j++];
		}
		while (i < nl)Y_merge[n_merge++] = Yl[i++];
		while (j < nr)Y_merge[n_merge++] = Yr[j++];

		//取最近7个点计算
		min_dis = delta;
		for (i = 0; i < n_merge; ++i) {
			for (j = 1; j < 8 && (i + j < n_merge); ++j) {
				dis_temp = dis(Y_merge[i], Y_merge[i+j]);
				if (dis_temp < min_dis)min_dis = dis_temp;
			}
		}

		return min_dis;
	}
}

float dis(point pt1, point pt2) {
	float dx = pt1.x - pt2.x;
	float dy = pt1.y - pt2.y;
	return sqrt(dx*dx + dy * dy);
}

point * imalloc(int len) {
	int t = pool_p;
	pool_p += len;
	return pool + t;
}