// 遗传算法求函数f(x) = x^2在[0, 2^length-1]之间的最大值，染色体采用length位编码
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define GENERATION 10           // 遗传代数
#define P_crossoverOVER 0.8         // 交叉概率，一般为0.6~1.0
#define P_MUTATION 0.008        // 变异概率，一般为0.005~0.01

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

void init(int length, Indi *population, int size)
{
    int i, limit = 1 << length;
    for (i = 0; i < size; ++i) {
        population[i].chromosome = rand() % 32;
    }
}

void selection(Indi *population, int size, int *gene)
{
    int i, j;
    double p, tmp, sum;
    sum = 0;
    for (i = 0; i < size; ++i) {
        sum += population[i].degree;
    }
    for (i = 0; i < 2*size; ++i) {
        p = (double)rand() / RAND_MAX;
        tmp = 0;
        for (j = 0; j < size && p > tmp/sum; ++j) {
            tmp += population[j].degree;
        }
        gene[i] = population[j-1].chromosome;
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

int crossover(int length, Indi *population, int size, int *gene)
{
    int i, crossover_point1, crossover_point2, father, mother;
    for (i = 0; i < size; ++i) {
        if (happened(P_crossoverOVER)) {
            crossover_point1 = rand() % length;
            // one point crossoverover
            if (rand() % 2 == 1) {
                father = get_bits(gene[i*2], 0, crossover_point1);
                mother = get_bits(gene[i*2+1], crossover_point1, length - crossover_point1);
                population[i].chromosome = father | (mother << crossover_point1);
            // two points crossoverover
            } else {
                while ((crossover_point2 = rand() % length) == crossover_point1) {
                    continue;
                }
                if (crossover_point1 > crossover_point2) {
                    swap(&crossover_point1, &crossover_point2);
                }
                father = get_bits(gene[i*2], 0, crossover_point1);
                population[i].chromosome = father;
                father = get_bits(gene[i*2], crossover_point2, length - crossover_point2);
                population[i].chromosome |= father << crossover_point2;
                mother = get_bits(gene[i*2+1], crossover_point1, crossover_point2 - crossover_point1);
                population[i].chromosome |= mother << crossover_point1;
            }
        }
    }
}

int mutation(int length, Indi *population, int size)
{
    int i;
    for (i = 0; i < size; ++i) {
        if (happened(P_MUTATION)) {
            population[i].chromosome ^= 1 << rand() % length;
        }
    }
}

void print_best(Indi *population, int size)
{
    int i, best = 0;
    double sum = population[0].degree;
    for (i = 1; i < size; ++i) {
        sum += population[i].degree;
        if (population[i].degree > population[best].degree) {
            best = i;
        }
    }
    printf("最优个体为%4d(%5lf)，平均适应度为%5.3lf。\n", population[best].chromosome, population[best].degree, sum/size);
}

void evaluate(Indi *population, int size)
{
    int i;
    for (i = 0; i < size; ++i) {
        population[i].degree = fit(population[i].chromosome);
    }
}

void heredity(int length, int size)
{
    int i;
    int *parent = (int *)malloc(size * 2 * sizeof(int));
    Indi *population = (Indi *)malloc(size * sizeof(Indi));
    init(length, population, size);
    evaluate(population, size);
    for (i = 1; i <= GENERATION; ++i) {
        selection(population, size, parent);
        crossover(length, population, size, parent);
        mutation(length, population, size);
        evaluate(population, size);
        printf("第%2d代中", i);
        print_best(population, size);
    }
    free(parent);
    free(population);
}

int main(void)
{
    int length, size;
    srand(time(NULL));
    printf("请输入位串长度：");
    scanf("%d", &length);
    printf("请输入种群规模：");
    scanf("%d", &size);
    heredity(length, size);
    return 0;
}
