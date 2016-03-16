#include <stdio.h>

void binary_insertion_sort(int *a, int n)
{
	int i, j, t, low, high, mid;
	for (i = 1; i < n; ++i)
	{
		low = 0;
		high = i - 1;
		t = a[i];
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (t < a[mid])
				high = mid - 1;
			else
				low = mid + 1;
		}
		for (j = i; j > mid; --j)
			a[j] = a[j-1];
		a[low] = t;
	}
}

int main(void)
{
	int a[10], i, n;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	binary_insertion_sort(a, n);

	for (i = 0; i < n; ++i)
		printf("%d ", a[i]);
	putchar('\n');

	return 0;
}
