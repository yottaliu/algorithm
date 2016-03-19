// 背包问题
// 有N件物品和一个容量为V的背包。第i件物品的重量是weight[i-1]，价值是val[i-1]。求解将哪些物品装入背包可使价值总和最大。
#include <stdio.h>
#define N 5
#define V 9
#define max(a, b) ((a) > (b) ? a : b)

int main(void)
{
	int item, capacity;
	int weight[N] = {3, 5, 2, 7, 4};
	int val[N] = {2, 4, 1, 6, 5};
	int f[N+1][V+1];
	for (item = 0; item <= N; ++item)
		f[item][0] = 0; // 容量为0时不放东西
	for (capacity = 0; capacity <= V; ++capacity)
		f[0][capacity] = 0; // 没有物品，背包为空

	for (item = 1; item <= N; ++item)
		for (capacity = 1; capacity <= V; ++capacity)
			if (weight[item-1] > capacity) // 如果背包的容量放不下,则不放入背包
				f[item][capacity] = f[item-1][capacity];
			else
				f[item][capacity] = max(f[item-1][capacity], f[item-1][capacity-weight[item-1]] + val[item-1]); // 转移方程式

	printf("%d\n", f[N][V]);
	return 0;
}
