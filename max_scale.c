#include <stdio.h>
#include <stdlib.h>
typedef struct Pair
{
	long long above;
	long long below;
}pair; // 用来保存分数
long long find(long long a, long long b) // 找最大公约数
{
	long long c;
	c = a % b;
	while (c)
	{
		a = b;
		b = c;
		c = a % b;
	}
	return b;
}
void simplify(pair * p) // 分数化简
{
	long long match;
	for (match = find(p->above, p->below); match != 1; match = find(p->above, p->below))
	{
		p->above /= match;
		p->below /= match;
	}
}
int comp_long_long(const void * x, const void * y) // 比较两个long long
{
	
	if (*(long long*)x - *(long long*)y < 0)
		return -1;
	else if(*(long long*)x == *(long long*)y)
		return 0;
	else
		return 1;
}
int comp_pair(const void * x, const void * y) // 比较两个分数
{
	
	if ((double)((pair*)x)->above / ((pair*)x)->below - (double)((pair*)y)->above / ((pair*)y)->below < 0)
		return -1;
	else if((double)((pair*)x)->above / ((pair*)x)->below == (double)((pair*)y)->above / ((pair*)y)->below)
		return 0;
	else
		return 1;
}
int main(void)
{
	int i, n;
	long long *a;
	pair one;
	pair * p;
	scanf("%d", &n);
	a = (long long*) malloc(n * sizeof(long long));
	for (i = 0; i < n; ++i)
		scanf("%lld", &a[i]);
	qsort(a, n, sizeof(long long), comp_long_long);

	// 把分数存入并且化简，然后按分数大小排序
	p = (pair*) malloc((n-1) * sizeof(pair));
	for (i = 0; i < n-1; ++i)
	{
		p[i].above = a[i+1];
		p[i].below = a[i];
		simplify(&p[i]);
	}
	qsort(p, n-1, sizeof(pair), comp_pair);

	// 找到第一个值不为1的最小分数，其余分数依次除以这个最小分数
	for (i = 0; i < n-1 && p[i].above == 1; ++i)
		continue;
	one = p[i];
	for (i++; i < n-1; ++i)
	{
		// 排除连续两个相同的分数
		if (p[i].above != p[i-1].above || p[i].below != p[i-1].below)
		{
			one.above = p[i].above / one.above;
			one.below = p[i].below / one.below;
		}
	}

	// 打印最终结果
	printf("%lld/%lld\n", one.above, one.below);
	return 0;
}
