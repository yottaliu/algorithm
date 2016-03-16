#include <stdio.h>
#include <stdlib.h>

void merge(int *a, int left, int mid, int right, int *temp)
{
	int i = left, m = mid, j = mid+1, n = right, k = 0;
	while (i <= m && j <= n)
	{
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	while (i <= m)
		temp[k++] = a[i++];
	while (j <= n)
		temp[k++] = a[j++];
	for (i = 0; i < k; ++i)
		a[left+i] = temp[i];
}

void mergesort(int *a, int left, int right, int *temp)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2; // 将数组分解
		mergesort(a, left, mid, temp); // 将前面一部分用递归的方法排序
		mergesort(a, mid+1, right, temp); // 将后面一部分用递归的方法排序
		merge(a, left, mid, right, temp); // 将两个部分合并
	}
}

int merge_sort(int *a, int n)
{
	int *p = (int *) malloc(n * sizeof(int));
	if (p == NULL)
		return 0;
	mergesort(a, 0, n-1, p);
	free(p);
	return 1;
}

int main(void)
{
	int a[10], i, n;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	merge_sort(a, n);

	for (i = 0; i < n; ++i)
		printf("%d ", a[i]);
	putchar('\n');

	return 0;
}
