#include <stdio.h>
int h[101]; // 用来存放堆的数组
int n; // 用来存放堆中元素的个数，也就是堆的大小

// 交换函数，用来存储堆中元素的个数，也就是堆的大小
void swap(int x, int y)
{
	int t;
	t = h[x];
	h[x] = h[y];
	h[y] = t;
}

// 向下调整函数
void siftdown(int i) // 传入一个需要向下调整的节点编号i，这里传入1，即从堆的顶点开始向下调整
{
	int t, flag = 0; // flag用来标记是否需要继续向下调整
	// 当i结点有儿子（其实是至少有左儿子的情况下）并且有需要继续调整的时候，循环就执行
	while (i*2 <= n && flag == 0)
	{
		// 首先判断它和左儿子的关系，并用t记录值较大的结点编号
		if (h[i] < h[i*2])
			t = i * 2;
		else
			t = i;
		// 如果它有右儿子，再对右儿子进行讨论
		if (i*2+1 <= n)
		{
			// 如果右儿子的值更大，更新较大的结点编号
			if (h[t] < h[i*2+1])
				t = i*2+1;
		}
		// 如果发现最大的结点编号不是自己，说明子结点中有比父结点更大的
		if (t != i)
		{
			swap(t, i); // 交换它们，注意swap函数需要自己来写
			i = t; // 更新i为刚才与它交换的儿子结点的编号，便于接下来继续向下调整
		}
		else
			flag = 1; // 否则说明当前的父结点已经比两个子结点都要大了，不需要再进行调整了
	}
}

// 建立堆的函数
void creat()
{
	int i;
	// 从最后一个非叶结点到第1个结点依次进行向上调整
	for (i = n/2; i >= 1; i--)
	{
		siftdown(i);
	}
}

// 堆排序
void heapsort()
{
	while (n > 1)
	{
		swap(1, n);
		n--;
		siftdown(1);
	}
}

int main()
{
	int i, num;
	// 读入n个数
	scanf("%d", &num);

	for (i = 1; i <= num; i++)
		scanf("%d", &h[i]);
	n = num;

	// 建堆
	creat();

	// 堆排序
	heapsort();

	// 输出
	for (i = 1; i <= num; i++)
		printf("%d ", h[i]);

	getchar();
	getchar();
	return 0;
}
