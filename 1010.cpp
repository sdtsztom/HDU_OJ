/*
 * 答案来自网上参考，但是有部分改良(去除多余代码),并简化成自己的风格
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
char map[10][10]; //7*7
int book[10][10];
int p, q, n, m, t, flag;
int next[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} }; //右下左上 

int check(int x, int y, int t) {
	int temp = t-abs(p - x)-abs(q - y);
	return temp < 0 || temp & 1;
	//return temp < 0 || (t + abs(p - x) + abs(q - y) & 1);	//所有的和也是偶数，因为偶数位置到偶数位置需要偶数步
	//奇数位到奇数位要偶数步;奇数到偶数或者偶数到奇数需要奇数步		
}

void dfs(int x, int y, int step) { //走的步数即等于时间 
	int i, tx, ty;
	if (x == p && y == q) { //到达门 
		if (step == t) flag = 1;
		return;
	}
	if (step >= t) return; //!!!剪枝 超时或没走到 
	if (check(x,y,t-step)) return;
	//剪枝：如果剩余的步数不足以走到出口，且必须是偶数，偶-偶=偶，奇-奇=偶
	for (i = 0; i < 4; i++) { //尝试4个方向 
		tx = x + next[i][0];
		ty = y + next[i][1]; //下一步的坐标
		if (tx<1 || tx>n || ty<1 || ty>m) //是否越界 
			continue;
		if (book[tx][ty] == 0 && map[tx][ty] != 'X') {
			book[tx][ty] = 1; //标记已走过 
			dfs(tx, ty, step + 1);
			if (flag) return; //有一个方案成功及时结束 
			book[tx][ty] = 0; //回溯 
		}
	}
	return;
}
int main() {
	int i, j, startx, starty, wall;
	while (scanf("%d%d%d", &n, &m, &t)) {
		getchar();
		if (n == 0 && m == 0 && t == 0) break;
		flag = wall = 0;
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= m; j++) {
				map[i][j] = getchar();
				if (map[i][j] == 'S') {startx = i;starty = j;}
				else if (map[i][j] == 'D') {p = i;q = j;}
				else if (map[i][j] == 'X')wall++;
			}
			getchar();
		}
		if (t > n*m - wall) printf("NO\n");
		else {
			memset(book, 0, sizeof(book)); //清零标记 
			book[startx][starty] = 1; //标记初始的占位 
			dfs(startx, starty, 0);
			if (flag) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}