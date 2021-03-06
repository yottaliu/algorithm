/*
 * 水壶问题：给定两个水壶，一个可装4升水，另一个能装3升水。水壶上没有任何度量标记。有一水龙头可用来往壶中灌水，问题是怎样在能装4升的水壶里恰好只装2升水。
 * 思路：设两个水壶的水量为(X, Y)。初始状态为(0, 0)，终止状态为(2, Y)。一共有6种操作，应用这6种操作使得从初始状态到达终止状态，期间不出现重复的状态，便可得出一种解法。
 * 程序可修改X_SIZE, Y_SIZE和end进行扩展，比如改为6升和5升的水壶，要求得到3升水。
 */
#include <stdio.h>
#define X_SIZE 4
#define Y_SIZE 3

typedef struct State
{
    int x;
    int y;
    int f;
}state;

state begin = {0, 0, 0};
state end = {2};

state operate(state now, int op)
{
    int tmp;

    switch(op) {
    case 0:
        now.x = X_SIZE;
        break;
    case 1:
        now.y = Y_SIZE;
        break;
    case 2:
        now.x = 0;
        break;
    case 3:
        now.y = 0;
        break;
    case 4:
        if (now.x + now.y < X_SIZE) {
            now.x += now.y;
            now.y = 0;
        } else {
            tmp = X_SIZE - now.x;
            now.x = X_SIZE;
            now.y -= tmp;
        }
        break;
    case 5:
        if (now.x + now.y < Y_SIZE) {
            now.y += now.x;
            now.x = 0;
        } else {
            tmp = Y_SIZE - now.y;
            now.y = Y_SIZE;
            now.x -= tmp;
        }
        break;
    }

    return now;
}

void bfs(void)
{
    int i, j, k, count;
    int head, tail;
    state queue[(X_SIZE+1)*(Y_SIZE+1)];
    int seq[(X_SIZE+1)*(Y_SIZE+1)];
    int visited[X_SIZE+1][Y_SIZE+1];
    int appeared[X_SIZE+1][Y_SIZE+1];
    state tmp;

    for (i = 0; i < X_SIZE+1; ++i) {
        for (j = 0; j < Y_SIZE+1; ++j) {
            visited[i][j] = 0;
        }
    }
    head = tail = 0;
    queue[tail++] = begin;
    visited[begin.x][begin.y] = 1;
    while (head < tail) {
        for (i = 0; i < X_SIZE+1; ++i) {
            for (j = 0; j < Y_SIZE+1; ++j) {
                appeared[i][j] = 0;
            }
        }
        for (i = 0; i < 6; ++i) {
            tmp = operate(queue[head], i);
            appeared[tmp.x][tmp.y] = 1;
        }
        for (i = 0; i < X_SIZE+1; ++i) {
            for (j = 0; j < Y_SIZE+1; ++j) {
                if (appeared[i][j] && !visited[i][j]) {
                    tmp.x = i;
                    tmp.y = j;
                    tmp.f = head;
                    queue[tail++] = tmp;
                    visited[i][j] = 1;
                    if (tmp.x == end.x) {
                        count = 0;
                        seq[count++] = tail-1;
                        while (tmp.f != 0) {
                            seq[count++] = tmp.f;
                            tmp = queue[tmp.f];
                        }
                        seq[count] = tmp.f;
                        for (k = count; k >= 0; --k) {
                            printf("(%d, %d) ", queue[seq[k]].x, queue[seq[k]].y);
                        }
                        printf("\n\n");
                    }
                }
            }
        }
        head++;
    }
}

int main(void)
{
    bfs();
    return 0;
}
