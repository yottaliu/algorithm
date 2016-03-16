#include <stdio.h>

void bubble_sort(int *a, int n)
{
	int i, j, t, flag;
	flag = 1;
	for (i = 0; i < n-1 && flag; ++i)
	{
		flag = 0;
		for (j = 1; j < n-i; ++j)
			if (a[j] < a[j-1])
			{
				t = a[j];
				a[j] = a[j-1];
				a[j-1] = t;
				flag = 1;
			}
	}
}

int main(void)
{
	int a[10], i, n;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	bubble_sort(a, n);

	for (i = 0; i < n; ++i)
		printf("%d ", a[i]);
	putchar('\n');

	return 0;
}
