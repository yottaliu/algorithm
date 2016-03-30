/*
 * 第七届蓝桥杯c/c++ B组第10题
 * 最大比例
 * X星球的某个大奖赛设了M级奖励。每个级别的奖金是一个正整数。
 * 并且，相邻的两个级别间的比例是个固定值。
 * 也就是说：所有级别的奖金数构成了一个等比数列。比如：
 * 16,24,36,54
 * 其等比值为：3/2
 * 现在，我们随机调查了一些获奖者的奖金数。
 * 请你据此推算可能的最大的等比值。
 * 输入格式：
 * 第一行为数字N，表示接下的一行包含N个正整数
 * 第二行N个正整数Xi(Xi<1 000 000 000 000)，用空格分开。每个整数表示调查到的某人的奖金数额
 * 要求输出：
 * 一个形如A/B的分数，要求A、B互质。表示可能的最大比例系数
 * 测试数据保证了输入格式正确，并且最大比例是存在的。
 * 例如，输入：
 * 3
 * 1250 200 32
 * 程序应该输出：
 * 25/4
 * 再例如，输入：
 * 4
 * 3125 32 32 200
 * 程序应该输出：
 * 5/2
 * 再例如，输入：
 * 3
 * 549755813888 524288 2
 * 程序应该输出：
 * 4/1
 * 资源约定：
 * 峰值内存消耗 < 256M
 * CPU消耗 < 3000ms
 * 请严格按要求输出，不要画蛇添足地打印类似：“请您输入...” 的多余内容。
 * 所有代码放在同一个源文件中，调试通过后，拷贝提交该源码。
 * 注意: main函数需要返回0
 * 注意: 只使用ANSI C/ANSI C++ 标准，不要调用依赖于编译环境或操作系统的特殊函数。
 * 注意: 所有依赖的函数必须明确地在源文件中 #include <xxx>， 不能通过工程设置而省略常用头文件。
 * 提交时，注意选择所期望的编译器类型。
 */
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
