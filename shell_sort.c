#include <stdio.h>

void shell_sort(int *a, int n)
{
	int i, t, gap = n/2, flag = 1;
	while(gap > 1 || flag)
	{
		flag = 0;
		for(i = 0; i+gap < n; ++i)
			if(a[i] > a[i+gap])
			{
				t = a[i];
				a[i] = a[i+gap];
				a[i+gap] = t;
				flag = 1;
			}
		if(gap > 1)
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
