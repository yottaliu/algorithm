// 遗传算法求函数f(x) = x^2在[0, 31]之间的最大值，染色体采用5位编码
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define GENERATION 10
#define P_CROSS 0.9
#define P_MUTATE 0.001

typedef struct Individual {
    int chromosome;
    double degree;
}Indi;

double fit(int individual)
{
    return (double)individual * individual;
}

int happened(double probability)
{
    return (double)rand()/RAND_MAX < probability;
}

void init(Indi *pop, int n)
{
    int i, tmp;
    for (i = 0; i < n; ++i) {
        tmp = rand() % 32;
        pop[i].chromosome = tmp;
        pop[i].degree = fit(tmp);
    }
}

void pick(Indi *pop, int n, int *gene)
{
    int i, j;
    double p, tmp, sum;
    sum = 0;
    for (i = 0; i < n; ++i) {
        sum += pop[i].degree;
    }
    for (i = 0; i < 2*n; ++i) {
        p = (double)rand() / RAND_MAX;
        tmp = 0;
        for (j = 0; j < n && p > tmp/sum; ++j) {
            tmp += pop[j].degree;
        }
        gene[i] = pop[j-1].chromosome;
    }
}

unsigned int get_bits(unsigned int num, int begin, int bits)
{
    int i;
    unsigned int mask = 0;
    for (i = 0; i < bits; ++i) {
        mask <<= 1;
        mask |= 1;
    }
    return ((unsigned int)num >> begin) & mask;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int cross(Indi *pop, int n, int *gene)
{
    int i, cross_point1, cross_point2, father, mother;
    for (i = 0; i < n; ++i) {
        if (happened(P_CROSS)) {
            cross_point1 = rand() % 5;
            // one point exchange
            if (rand() % 2 == 1) {
                father = get_bits(gene[i*2], 0, cross_point1);
                mother = get_bits(gene[i*2+1], cross_point1, 5 - cross_point1);
                pop[i].chromosome = father | (mother << cross_point1);
            // two points exchange
            } else {
                while ((cross_point2 = rand() % 5) == cross_point1) {
                    continue;
                }
                if (cross_point1 > cross_point2) {
                    swap(&cross_point1, &cross_point2);
                }
                father = get_bits(gene[i*2], 0, cross_point1);
                pop[i].chromosome = father;
                father = get_bits(gene[i*2], cross_point2, 5 - cross_point2);
                pop[i].chromosome |= father << cross_point2;
                mother = get_bits(gene[i*2+1], cross_point1, cross_point2 - cross_point1);
                pop[i].chromosome |= mother << cross_point1;
            }
        }
    }
}

int mutate(Indi *pop, int n)
{
    int i;
    for (i = 0; i < n; ++i) {
        if (happened(P_MUTATE)) {
            pop[i].chromosome ^= 1 << rand() % 5;
        }
    }
}

void print_best(Indi *pop, int n)
{
    int i, best = 0;
    double sum = pop[0].degree;
    for (i = 1; i < n; ++i) {
        sum += pop[i].degree;
        if (pop[i].degree > pop[best].degree) {
            best = i;
        }
    }
    printf("最优个体为%4d(%5lf)，平均适应度为%5.3lf。\n", pop[best].chromosome, pop[best].degree, sum/n);
}

void evaluate(Indi *pop, int n)
{
    int i;
    for (i = 0; i < n; ++i) {
        pop[i].degree = fit(pop[i].chromosome);
    }
}

void heredity(int n)
{
    int i;
    int *parent = (int *)malloc(n * 2 * sizeof(int));
    Indi *pop = (Indi *)malloc(n * sizeof(Indi));
    init(pop, n);
    for (i = 1; i <= GENERATION; ++i) {
        pick(pop, n, parent);
        cross(pop, n, parent);
        mutate(pop, n);
        evaluate(pop, n);
        printf("第%2d代中", i);
        print_best(pop, n);
    }
    free(parent);
    free(pop);
}

int main(void)
{
    int n;
    srand(time(NULL));
    printf("请输入种群规模：");
    scanf("%d", &n);
    heredity(n);
    return 0;
}
