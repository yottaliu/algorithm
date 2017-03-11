/*
 * N皇后问题
 */
#include <stdio.h>
#define N 8

int col[N+1];
int count = 0;

int available(int r, int c)
{
    int i;
    for (i = 1; i < r; ++i) {
        if (c == col[i] || r-i == c-col[i] || r-i == col[i]-c) {
            return 0;
        }
    }
    return 1;
}

void dfs(int row)
{
    int r, c;

    if (row == N+1) {
        for (r = 1; r <= N; ++r) {
            printf("(%d, %d) ", r, col[r]);
        }
        printf("\n\n");
        count++;
        return;
    }

    for (c = 1; c <= N; ++c) {
        if (available(row, c)) {
            col[row] = c;
            dfs(row+1);
        }
    }
}

int main(void)
{
    dfs(1);
    printf("%d distinct solutions\n", count);
    return 0;
}
