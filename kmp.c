#include <stdio.h>
#include <string.h>
void get_next(char *p, int *next)
{
	int j, k, pLen;
	next[0] = -1;
	k = -1;
	j = 0;
	pLen = strlen(p);
	while (j < pLen-1)
	{
		if (k == -1 || p[j] == p[k])
		{
			++j;
			++k;
			if (p[j] != p[k])
				next[j] = k;
			else
				next[j] = next[k];
		}
		else
		{
			k = next[k];
		}
	}
}

int kmp_search(char *s, char *p, int *next)
{
	int i, j, sLen, pLen;
	i = 0;
	j = 0;
	sLen = strlen(s);
	pLen = strlen(p);
	while (i < sLen && j < pLen)
	{
		if (j == -1 || s[i] == p[j])
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];
		}
	}
	if (j == pLen)
		return i - j;
	else
		-1;
}

int main(void)
{
	char *s = "BBC ABCDAB ABCDABCDABDE";
	char *p = "ABCDABD";
	int next[7];
	get_next(p, next);
	printf("%d\n", kmp_search(s, p, next));
	return 0;
}
