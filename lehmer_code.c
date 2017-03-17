/*
 * n个元素有n!种排列，对这些排列进行编码，使得每种排列对应唯一一个编号，这种编码叫做Lehmer code。
 * 这个程序可以根据给定的排列编号求出对应的Lehmer code，进而得出这个排列。
 */
#include <stdio.h>
#define N 30

long long int factorial(int num)
{
    long long int ret = 1;
    while (num > 1) {
        ret *= (long long int)num;
        num--;
    }
    return ret;
}

void integer_to_lehmer_code(long long int num, int *code, int n)
{
    int i;
    long long int a, b, fac;
    b = num;
    for (i = 0; i < n; ++i) {
        a = b;
        fac = factorial(n-1-i);
        b = a % fac;
        code[i] = (int)(a / fac);
    }
}

void lehmer_code_to_permutation(int *code, int n, int *perm)
{
    int i, k, count, visited[N];
    for (i = 0; i < n; ++i) {
        visited[i] = 0;
    }
    for (i = 0; i < n; ++i) {
        count = 0;
        for (k = 0; k < n; ++k) {
            if (!visited[k]) {
                if (count == code[i]) {
                    visited[k] = 1;
                    break;
                }
                count++;
            }
        }
        perm[i] = k;
    }
}

int main(void)
{
    int k, n;
    int code[N], perm[N];
    long long int i, num;
    scanf("%d", &n);
    num = factorial(n);
    for (i = 0; i < num; ++i) {
        printf("%6lld\t\t", i);
        integer_to_lehmer_code(i, code, n);
        for (k = 0; k < n; ++k) {
            printf("%d", code[k]);
        }
        putchar('\t');
        lehmer_code_to_permutation(code, n, perm);
        for (k = 0; k < n; ++k) {
            printf("%c", 'a' + perm[k]);
        }
        putchar('\n');
    }
    return 0;
}
