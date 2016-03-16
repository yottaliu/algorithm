#include <stdio.h>

void insertion_sort(int *a, int n)
{
	int i, j, key;
	for (i = 1; i < n; ++i)
	{
		key = a[i];
		for (j = i - 1; j >= 0 && a[j] > key; --j)
			a[j+1] = a[j];
		a[j+1] = key;
	}
}

int main(void)
{
	int a[10], i, n;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	insertion_sort(a, n);

	for (i = 0; i < n; ++i)
		printf("%d ", a[i]);
	putchar('\n');

	return 0;
}
