#include <stdio.h>
void shell_sort(int *a, int n)
{
	int i, j, t, gap = n / 2;
	while (gap > 0)
	{
		for (i = gap; i < n; ++i)
		{
			t = a[i];
			for (j = i-gap; j >= 0 && a[j] > t; j -= gap)
				a[j+gap] = a[j];
			a[j+gap] = t;
		}
		gap /= 2;
	}
}

int main(void)
{
	int a[10], i, n;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	shell_sort(a, n);

	for (i = 0; i < n; ++i)
		printf("%d ", a[i]);
	putchar('\n');

	return 0;
}
