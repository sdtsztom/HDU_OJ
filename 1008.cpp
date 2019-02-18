/*
 * 水题一道
 */

#include <iostream>
#include<cmath>

using namespace std;

int main() {
	int n;
	int a[100];
	int sum;
	int i;
	while (cin >> n && n) {
		sum = 0;
		for (i = 0; i < n; i++)cin >> a[i];

		sum = 6 * a[0] + 5 * n;

		for (int i = 1; i < n; i++) {
			if (a[i] > a[i - 1])sum += 6 * (a[i] - a[i - 1]);
			else sum += (a[i - 1] - a[i]) << 2;
		}

		cout << sum << endl;
	}
}