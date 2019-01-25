/*
 * 为了解决malloc分配内存导致的TLE的问题，采用提前分配空间的方法
 * HDU OJ 提供了大约32mb的内存上限，因此使用了Y_digest来节省空间
 * 同时解决了由于使用cin来解析输入导致的超时问题
 * 并且还在计算时加入限制来减少计算量
 * 再上一个版本的基础上加入了trick(筛选)来speed up
 * 但是测试以后并没有加快速度:(
 */

#include<iostream>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<string.h>
#include<cstdlib>
#pragma warning (disable:4996)
#define MAXSIZE 100000

using namespace std;

typedef struct {
	int index;
	double x;
	double y;
}point;

enum SIDE{LEFT,RIGHT};

typedef struct {
	int index;
	SIDE side;
}Y_digest;

bool cmp_x(point p1, point p2);
bool cmp_y(point p1, point p2);
double find_min_dis(int low, int high, point X[], Y_digest Y[]);
double dis(point pt1, point pt2);
Y_digest * imalloc(int len);
void sift();

point X[MAXSIZE];
point Y[MAXSIZE];
Y_digest Y_merge[MAXSIZE];
Y_digest Y_index[MAXSIZE];
Y_digest pool[18 * MAXSIZE];
int pool_p = 0;

int N;

int main()
{
	int i;
	while (cin >> N && N != 0) {
		//reset pool point
		pool_p = 0;

		// store data
		for (i = 0; i < N; ++i) {
			scanf("%lf%lf", &X[i].x, &X[i].y);
			//cin >> X[i].x;
			//cin >> X[i].y;
		}

		// presort
		sort(X, X + N, cmp_x);
		//for (i = 0; i < N; ++i)X[i].index = i;
		//memcpy(Y, X, N * sizeof(point));
		//sort(Y, Y + N, cmp_y);

		// 筛选
		sift();
		for (i = 0; i < N; ++i)X[i].index = i;
		memcpy(Y, X, N * sizeof(point));
		sort(Y, Y + N, cmp_y);

		// 生成index数组
		for (i = 0; i < N; ++i)Y_index[i].index = Y[i].index;

		double min_dis = find_min_dis(0, N - 1, X, Y_index);

		cout << fixed << setprecision(2)<< min_dis/2 <<endl;
	}
}

bool cmp_x(point p1, point p2) { return p1.x < p2.x; }
bool cmp_y(point p1, point p2) { return p1.y < p2.y; }

double find_min_dis(int low, int high, point X[], Y_digest Y[]) {
	if (high - low == 1)return dis(X[high], X[low]);  //两个点
	else if (high - low == 2) {                       //三个点
		double dis1 = dis(X[high], X[high - 1]);
		double dis2 = dis(X[high], X[low]);
		double dis3 = dis(X[high - 1], X[low]);
		return min(min(dis1, dis2), dis3);
	}
	else {                                      // 三个点以上，需要分治
		int mid = (low + high) / 2;
		double mid_line = (X[mid].x + X[mid + 1].x) / 2;
		int len_left = mid - low + 1;
		int len_right = high - mid;
		Y_digest *Yl, *Yr;
		int nl = 0, nr = 0, n_merge = 0;
		int i, j;
		double min_dis, min_dis_left, min_dis_right, dis_temp;
		double delta;
		double left_bound, right_bound;

		Yl = imalloc(len_left);
		Yr = imalloc(len_right);

		//对Y中的点进行划分
		for (i = 0; i < high - low + 1; ++i) {
			if (Y[i].index <= mid) {
				Yl[nl].index = Y[i].index;
				Yl[nl++].side = LEFT;
			}
			else {
				Yr[nr].index = Y[i].index;
				Yr[nr++].side = RIGHT;
			}
		}

		min_dis_left = find_min_dis(low, mid, X, Yl);
		min_dis_right = find_min_dis(mid + 1, high, X, Yr);
		delta = min(min_dis_left, min_dis_right);  //使用delta这个参数名是依据算法导论书中的命名
		left_bound = mid_line - delta;
		right_bound = mid_line + delta;

		//筛选出再S区域内的Y
		nl = nr = 0;
		//为了节省内存，直接在原数组上进行操作
		for (i = 0; i < len_left; ++i)if (X[Yl[i].index].x >= left_bound)Yl[nl++] = Yl[i];
		for (i = 0; i < len_right; ++i)if (X[Yr[i].index].x <= right_bound)Yr[nr++] = Yr[i];

		//合并所有的Y
		for (i = 0, j = 0; i < nl&&j < nr;) {
			if (X[Yl[i].index].y < X[Yr[j].index].y)Y_merge[n_merge++] = Yl[i++];
			else Y_merge[n_merge++] = Yr[j++];
		}
		while (i < nl)Y_merge[n_merge++] = Yl[i++];
		while (j < nr)Y_merge[n_merge++] = Yr[j++];

		//取最近7个点计算
		min_dis = delta;
		for (i = 0; i < n_merge; ++i) {
			for (j = 1; j < 8 && (i + j < n_merge); ++j) {
				if (Y_merge[i].side == Y_merge[i + j].side)continue;
				else if (X[Y_merge[i + j].index].y - X[Y_merge[i].index].y > delta)break;
				dis_temp = dis(X[Y_merge[i].index], X[Y_merge[i+j].index]);
				if (dis_temp < min_dis)min_dis = dis_temp;
			}
		}

		return min_dis;
	}
}

double dis(point pt1, point pt2) {
	double dx = pt1.x - pt2.x;
	double dy = pt1.y - pt2.y;
	return sqrt(dx*dx + dy * dy);
}

Y_digest * imalloc(int len) {
	int t = pool_p;
	pool_p += len;
	return pool + t;
}

void sift() {
	double min_Mdis, Mdis_i;
	double dx, dy,dx_t,dy_t;
	double Edis;
	int sift_table[MAXSIZE];
	int last_flag=1;
	int i,n;

	//sift_table init
	for (i = 0; i < MAXSIZE; ++i)sift_table[i] = 1;

	// 用X
	min_Mdis = 1e5;	//代表infinite
	for (i = 1; i < N; ++i) {
		dx_t = X[i].x - X[i - 1].x;
		dy_t = abs(X[i].y - X[i - 1].y);
		Mdis_i = dx_t+dy_t;
		if (Mdis_i < min_Mdis) {
			min_Mdis = Mdis_i;
			dx = dx_t;
			dy = dy_t;
		}
	}
	// 用Y
	//for (i = 1; i < N; ++i) {
	//	dx_t = abs(Y[i].x - Y[i - 1].x);
	//	dy_t = Y[i].y - Y[i - 1].y;
	//	Mdis_i = dx_t + dy_t;
	//	if (Mdis_i < min_Mdis) {
	//		min_Mdis = Mdis_i;
	//		dx = dx_t;
	//		dy = dy_t;
	//	}
	//}

	Edis = sqrt(dx * dx + dy * dy);

	//开始筛选
	// 用X
	for (i=1; i < N; ++i) {
		if ((X[i].x - X[i - 1].x) > Edis) {
			if (last_flag)sift_table[i - 1] = 0;
			last_flag = 1;
		}
		else last_flag = 0;
	}
	// 用Y
	//last_flag = 1;
	//for (i = 1; i < N; ++i) {
	//	if ((Y[i].y - Y[i - 1].y) > Edis) {
	//		if (last_flag)sift_table[Y[i - 1].index] = 0;	//注意这一行与上面不一样
	//		last_flag = 1;
	//	}
	//	else last_flag = 0;
	//}

	// 留下合适的点
	n = 0;
	for (i = 0; i < N; ++i)if (sift_table[i])X[n++] = X[i];
	N = n;
}