#include <stdio.h>

void quicksort(int *a, int left, int right)
{
	int i, j, temp, t;
	if (left > right)
		return;
	i = left;
	j = right;
	temp = a[left];
	while (i < j)
	{
		while (i < j && a[j] >= temp)
			--j;
		while (i < j && a[i] <= temp)
			++i;
		if (i < j)
		{
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	a[left] = a[i];
	a[i] = temp;
	quicksort(a, left, i-1);
	quicksort(a, i+1, right);
}

void quick_sort(int *a, int n)
{
	quicksort(a, 0, n-1);
}

int main(void)
{
	int a[10], i, n;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	quick_sort(a, n);

	for (i = 0; i < n; ++i)
		printf("%d ", a[i]);
	putchar('\n');

	return 0;
}
