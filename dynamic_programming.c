// 背包问题
// 有N件物品和一个容量为V的背包。第i件物品的体积是c[i]，价值是v[i]。求解将哪些物品装入背包可使价值总和最大。
#include <stdio.h>

#define max(a, b) ((a) > (b) ? a : b)
int c[5] = {3, 5, 2, 7, 4};
int v[5] = {2, 4, 1, 6, 5};
int f[6][10] = {0};

int main(void)
{
	int i, j;
	for (i = 1; i < 6; i++)
		for (j = 1; j < 10; j++)
		{
			if (c[i] > j) // 如果背包的容量放不下c[i],则和不选c[i]
				f[i][j] = f[i-1][j];
			else
				f[i][j] = max(f[i-1][j], f[i-1][j-c[i]] + v[i]); // 转移方程式
		}
	printf("%d\n", f[5][9]);
	return 0;
}
