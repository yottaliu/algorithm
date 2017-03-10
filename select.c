/*
 * 有编号为1,2,...,m的m颗珠子。要取出n颗，一共有C(m, n)种取法。
 * 现要把各种取法编号为1,2,...,C(m, n)，以便指定一个编号的取法，取出对应的唯一的珠子组合。
 */
#include <stdio.h>
#define MAX 50

int m, n, x, count;
int queue[MAX];

int fac(int n)
{
    int i;
    for (i = n-1; i > 1; --i) {
        n *= i;
    }
    if (n == 0) {
        n = 1;
    }
    return n;
}

int select_n_from_m(int n, int m)
{
    return fac(m) / fac(n) / fac(m-n);
}

void dfs(int step)
{
    int i;
    if (step == n+1) {
        count++;
        if (count == x) {
            printf("%d: \t", x);
            printf("(%d", queue[1]);
            for (i = 2; i < n; ++i) {
                printf(", %d", queue[i]);
            }
            if (n == 1) {
                putchar(')');
            } else {
                printf(", %d)", queue[i]);
            }
            putchar('\n');
        }
        return;
    }

    for (i = queue[step-1]+1; i <= m; ++i) {
        queue[step] = i;
        dfs(step+1);
    }
}

int main(void)
{
    int i, j;
    scanf("%d%d", &m, &n);
    for (i = 1; i <= select_n_from_m(n, m); ++i) {
        for (j = 0; j < MAX; ++j) {
            queue[j] = 0;
        }
        queue[0] = 0;
        count = 0;
        x = i;
        dfs(1);
    }
    return 0;
}
