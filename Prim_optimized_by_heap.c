#include <stdio.h>
int dis[7], book[7] = {0}; // book数组用来记录哪些顶点已经放入生成树中
int h[7], pos[7], size; // h用来保存堆，pos用来存储每个顶点在堆中的位置，size为堆的大小

// 交换函数，用来交换堆中的两个元素的值
void swap(int x, int y)
{
	int t;
	t = h[x];
	h[x] = h[y];
	h[y] = t;

	// 同步更新pos
	t = pos[h[x]];
	pos[h[x]] = pos[h[y]];
	pos[h[y]] = t;
}

// 向下调整函数
void siftdown(int i) // 传入一个需要向下调整的结点编号
{
	int t, flag = 0; // flag用来标记是否需要继续向下调整
	while (i*2 <= size && flag == 0)
	{
		// 比较i和它左儿子i*2在dis中的值，并用t记录值较小的结点编号
		if (dis[h[i]] > dis[h[i*2]])
			t = i * 2;
		else
			t = i;
		// 如果它有右儿子，再对右儿子进行讨论
		if (i*2+1 <= size)
		{
			// 如果右儿子的值更小，更新较小的结点编号
			if (dis[h[t]] > dis[h[i*2+1]])
				t = i*2+1;
		}
		// 如果发现最小的结点编号不是自己，说明子结点中有比父结点更小的
		if (t != i)
		{
			swap(t, i); // 交换它们
			i = t; // 更新i为刚才与它交换的儿子结点的编号，便于接下来继续向下调整
		}
		else
			flag = 1; // 否则说明当前的父结点已经比两个子结点都要小了，不需要再进行调整了
	}
}

void siftup(int i) // 传入一个需要向上调整的结点编号i
{
	int flag = 0; // 用来标记是否需要继续向上调整
	if (i == 1)
		return; // 如果是堆顶，就返回，不需要调整了
	// 不在堆顶，并且当前结点i的值比父结点小的时候继续向上调整
	while (i != 1 && flag == 0)
	{
		// 判断是否比父结点的小
		if (dis[h[i]] < dis[h[i/2]])
			swap(i, i/2); // 交换它和它爸爸的位置
		else
			flag = 1; // 表示已经不需要调整了，当前结点的值比父结点的值要大
		i = i / 2; // 这句话很重要，更新编号i为它父结点的编号，从而便于下一次继续向上调整
	}
}

// 从堆顶取出一个元素
int pop()
{
	int t;
	t = h[1]; // 用一个临时变量记录堆顶点的值
	pos[t] = 0; // 其实这句要不要无所谓
	h[1] = h[size]; // 将堆的最后一个点赋值到堆顶
	pos[h[1]] = 1;
	size--; // 堆的元素减少1
	siftdown(1); // 向下调整
	return t; // 返回之前记录的堆顶点
}

int main()
{
	int n, m, i, j, k;
	// u、v、w和next的数组大小要根据实际情况来设置，此图是无向图，要比2*m的最大值要大1
	// first要比n的最大值要大1，要比2*m的最大值要大1
	int u[19], v[19], w[19], first[7], next[19];
	int inf = 99999999; // 用inf（infinity的缩写）存储一个我们认为的正无穷值
	int count = 0, sum = 0; // count用来记录生成树中顶点的个数，sum用来存储路径之和

	// 读入n和m，n表示顶点个数，m表示边的条数
	scanf("%d %d", &n, &m);

	// 开始读入边
	for (i = 1; i <= m; i++)
		scanf("%d %d %d", &u[i], &v[i], &w[i]);

	// 这里是无向图，所以需要将所有的边再反向存储一次
	for (i = m+1; i <= 2*m; i++)
	{
		u[i] = v[i-m];
		v[i] = u[i-m];
		w[i] = w[i-m];
	}

	// 开始使用邻接表存储边
	for (i = 1; i <= n; i++)
		first[i] = -1;
	for (i = 1; i <= 2*m; i++)
	{
		next[i] = first[u[i]];
		first[u[i]] = i;
	}

	// Prim核心部分开始
	// 将1号顶点加入生成树
	book[1] = 1; // 这里用book来标记一个顶点已经加入生成树
	count++;

	// 初始化dis数组，这里是1号顶点到其余各个顶点的初始距离
	dis[1] = 0;
	for (i = 2; i <= n; i++)
		dis[i] = inf;
	k = first[1];
	while (k != -1)
	{
		dis[v[k]] = w[k];
		k = next[k];
	}
	// 初始化堆
	size = n;
	for (i = 1; i <= size; i++)
	{
		h[i] = i;
		pos[i] = i;
	}
	for (i = size/2; i >= 1; i--)
	{
		siftdown(i);
	}
	pop(); // 先弹出一个堆顶元素，因为此时堆顶是1号顶点

	while (count < n)
	{
		j = pop();
		book[j] = 1;
		count++;
		sum = sum + dis[j];

		// 扫描当前顶点j所有的边，再以j为中间点，进行松弛
		k = first[j];
		while (k != -1)
		{
			if (book[v[k]] == 0 && dis[v[k]] > w[k])
			{
				dis[v[k]] = w[k]; // 更新距离
				siftup(pos[v[k]]); // 对该点在堆中进行向上调整
				// 提示：pos[v[k]]存储的是顶点v[k]在堆中的位置
			}
			k = next[k];
		}
	}

	printf("%d", sum); // 打印结果

	getchar();
	getchar();
	return 0;
}
