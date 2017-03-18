/*
 * 标题： 排列序数
 *
 * X星系的某次考古活动发现了史前智能痕迹。
 * 这是一些用来计数的符号，经过分析它的计数规律如下：
 * （为了表示方便，我们把这些奇怪的符号用a~q代替）
 *
 * abcdefghijklmnopq 表示0
 * abcdefghijklmnoqp 表示1
 * abcdefghijklmnpoq 表示2
 * abcdefghijklmnpqo 表示3
 * abcdefghijklmnqop 表示4
 * abcdefghijklmnqpo 表示5
 * abcdefghijklmonpq 表示6
 * abcdefghijklmonqp 表示7
 * .....
 *
 * 在一处石头上刻的符号是：
 * bckfqlajhemgiodnp
 *
 * 请你计算出它表示的数字是多少？
 *
 * 请提交该整数，不要填写任何多余的内容，比如说明或注释。
 *
 * 问题中的编码其实就是Lehmer code
 * 这是求Lehmer code的逆过程，思路是先由给出的排列求出这个排列的Lehmer code，再由Lehmer code倒推出这个排列的编号。
 */

#include <stdio.h>
#define N 17

void gen_factorial(long long int *fac)
{
    int i;
    fac[0] = 1;
    for (i = 1; i < N; ++i) {
        fac[i] = (long long int)i * fac[i-1];
    }
}

void permutation_to_lehmer_code(char *perm, int *code)
{
    int i, j, pos[N];
    for (i = 0; i < N; ++i) {
        pos[i] = i;
    }
    for (i = 0; i < N; ++i) {
        code[i] = pos[perm[i]-'a'];
        for (j = perm[i]-'a'+1; j < N; ++j) {
            pos[j]--;
        }
    }
}

long long int lehmer_code_to_integer(int *code, long long int *fac)
{
    int i;
    long long int num = 0;
    for (i = 1; i < N; ++i) {
        num += code[N-1-i] * fac[i];
    }
    return num;
}

int main(void)
{
    int i, j, pos[N], code[N];
    char perm[N+1];
    long long int fac[N];
    scanf("%s", perm);
    gen_factorial(fac);
    permutation_to_lehmer_code(perm, code);
    printf("%lld\n", lehmer_code_to_integer(code, fac));
    return 0;
}
