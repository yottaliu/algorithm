#include <stdio.h>

void selection_sort(int *a, int n)
{
	int i, j, min, t;
	for (i = 0; i < n-1; ++i)
	{
		min = i;
		for (j = i+1; j < n; ++j)
			if (a[j] < a[min])
				min = j;
		if (min != i)
		{
			t = a[i];
			a[i] = a[min];
			a[min] = t;
		}
	}
}

int main(void)
{
	int a[10], i, n;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	selection_sort(a, n);

	for (i = 0; i < n; ++i)
		printf("%d ", a[i]);
	putchar('\n');

	return 0;
}
