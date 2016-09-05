// 由（后序|先序)和中序遍历序列求二叉树的层序遍历序列
#include <stdio.h>
#define N 80
int main(void)
{
	int post[N], mid[N], level[N] = {0}, i, j, root, n, left, right, count;
    // int pre[N];          // 先序序列
	scanf("%d", &n);
	for (i = 0; i < n; ++i)
		scanf("%d", &post[i]);
	for (i = 0; i < n; ++i)
		scanf("%d", &mid[i]);

	// for (i = 0; i < n; ++i) {        // 先序
	for (i = n-1; i >= 0; --i) {        // 后序
		left = right = 0;
		for (j = 0; j < n; ++j) {
			if (post[i] == mid[j]) {
				root = j;
				break;
			}
			if (level[j])
				left = level[j];
		}
		for (; j < n; ++j) {
			if (level[j]) {
				right = level[j];
				break;
			}
		}
		level[root] = left >= right ? left+1 : right+1;
	}
	i = 1;
	count = 0;
	while(1) {
		for (j = 0; j < n; ++j) {
			if (level[j] == i) {
				++count;
				if (count == n) {
					printf("%d", mid[j]);
					return 0;
				}
				else
					printf("%d ", mid[j]);
			}
		}
		++i;
	}
}
