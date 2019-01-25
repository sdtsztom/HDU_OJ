/*
 *由于使用的是malloc，导致使用时间过长
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

point X[MAXSIZE];
point Y[MAXSIZE];

int main()
{
	int N;
	int i;
	while (cin >> N && N != 0) {
		// store data
		for (i = 0; i < N; ++i) {
			X[i].index=i;
			cin >> X[i].x;
			cin >> X[i].y;
		}

		memcpy(Y, X, MAXSIZE * sizeof(point));

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
		point *Yl, *Yr, *Yl_inS, *Yr_inS, *Y_merge;
		int nl = 0, nr = 0, n_merge = 0;
		int i, j;
		float min_dis, min_dis_left, min_dis_right, dis_temp;
		float delta;
		float left_bound, right_bound;

		Yl = (point*)malloc(len_left * sizeof(point));
		Yr = (point*)malloc(len_right * sizeof(point));
		//Yl_inS = (point*)malloc(len_left * sizeof(point));
		//Yr_inS = (point*)malloc(len_right * sizeof(point));
		Y_merge = (point*)malloc((high - low + 1) * sizeof(point));

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
		//for (i = 0; i < len_left; ++i)if (Yl[i].x >= left_bound)Yl_inS[nl++] = Yl[i];
		//for (i = 0; i < len_right; ++i)if (Yr[i].x <= right_bound)Yr_inS[nr++] = Yr[i];

		//为了节省内存，直接在原数组上进行操作
		for (i = 0; i < len_left; ++i)if (Yl[i].x >= left_bound)Yl[nl++] = Yl[i];
		for (i = 0; i < len_right; ++i)if (Yr[i].x <= right_bound)Yr[nr++] = Yr[i];

		//合并所有的Y
		//for (i = 0, j = 0; i < nl&&j < nr;) {
		//	if (Yl_inS[i].y < Yr_inS[j].y)Y_merge[n_merge++] = Yl[i++];
		//	else Y_merge[n_merge++] = Yr_inS[j++];
		//}
		//while (i < nl)Y_merge[n_merge++] = Yl_inS[i++];
		//while (j < nr)Y_merge[n_merge++] = Yr_inS[j++];
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
				dis_temp = dis(Y_merge[i], Y_merge[j]);
				if (dis_temp < min_dis)min_dis = dis_temp;
			}
		}

		//释放内存
		free(Yl);
		free(Yr);
		free(Y_merge);
		//free(Yl_inS);
		//free(Yr_inS);

		return min_dis;
	}
}

float dis(point pt1, point pt2) {
	float dx = pt1.x - pt2.x;
	float dy = pt1.y - pt2.y;
	return sqrt(dx*dx + dy * dy);
}
