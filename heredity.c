// 遗传算法求函数f(x) = x^2在[0, 2^length-1]之间的最大值，染色体采用length位编码
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define GENERATION 10           // 遗传代数
#define P_CROSSOVER 0.8         // 交叉概率，一般为0.6~1.0
#define P_MUTATION 0.008        // 变异概率，一般为0.005~0.01

typedef struct s_individual {
    unsigned int chromosome;
    double degree;
}Individual;

double fitness(unsigned int chromosome)
{
    return (double)chromosome * chromosome;
}

int happened(double probability)
{
    return (double)rand()/RAND_MAX < probability;
}

void init(int length, Individual *population, int size)
{
    int i, limit = 1 << length;
    for (i = 0; i < size; ++i) {
        population[i].chromosome = rand() % limit;
    }
}

void selection(Individual *population, int size, unsigned int *gene)
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
    return (num >> begin) & mask;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int crossover(int length, Individual *population, int size, unsigned int *gene)
{
    int i, j, k, choice, crossover_point1, crossover_point2, *crossover_point;
    unsigned int father, mother;
    for (i = 0; i < size; ++i) {
        if (happened(P_CROSSOVER)) {
            population[i].chromosome = 0;
            choice = rand() % 3;
            // one-point crossoverover
            if (choice == 0) {
                // 长度为length的染色体最多有length-1个隔点
                crossover_point1 = rand() % (length-1) + 1;
                father = get_bits(gene[i*2], 0, crossover_point1);
                mother = get_bits(gene[i*2+1], crossover_point1, length - crossover_point1);
                population[i].chromosome = father | (mother << crossover_point1);
            // two-point crossoverover
            } else if (choice == 1) {
                // 长度为length的染色体最多有length-1个隔点
                crossover_point1 = rand() % (length-1) + 1;
                while ((crossover_point2 = rand() % (length-1) + 1) == crossover_point1) {
                    continue;
                }
                if (crossover_point1 > crossover_point2) {
                    swap(&crossover_point1, &crossover_point2);
                }
                father = get_bits(gene[i*2], 0, crossover_point1);
                population[i].chromosome = father;
                mother = get_bits(gene[i*2+1], crossover_point1, crossover_point2 - crossover_point1);
                population[i].chromosome |= mother << crossover_point1;
                father = get_bits(gene[i*2], crossover_point2, length - crossover_point2);
                population[i].chromosome |= father << crossover_point2;
            // multipoint crossover
            } else {
                crossover_point = (int *)malloc((length+1) * sizeof(int));
                for (j = 1; j <= length-1; ++j) {
                    crossover_point[j] = 0;
                }
                // 长度为length的染色体最多有length-1个隔点
                for (j = 0; j < length-1; ++j) {
                    crossover_point[rand() % (length-1) + 1]++;
                }
                k = 0;
                crossover_point[k++] = 0;
                for (j = 1; j <= length-1; ++j) {
                    if (crossover_point[j] != 0) {
                        crossover_point[k++] = j;
                    }
                }
                crossover_point[k] = length;
                for (j = 0; j < k; ++j) {
                    if (j % 2 == 1) {
                        father = get_bits(gene[i*2], crossover_point[j], crossover_point[j+1] - crossover_point[j]);
                        population[i].chromosome |= father << crossover_point[j];
                    } else {
                        mother = get_bits(gene[i*2+1], crossover_point[j], crossover_point[j+1] - crossover_point[j]);
                        population[i].chromosome |= mother << crossover_point[j];
                    }
                }
                free(crossover_point);
            }
        }
    }
}

int mutation(int length, Individual *population, int size)
{
    int i;
    for (i = 0; i < size; ++i) {
        if (happened(P_MUTATION)) {
            population[i].chromosome ^= 1 << rand() % length;
        }
    }
}

void print_best(Individual *population, int size)
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

void evaluate(Individual *population, int size)
{
    int i;
    for (i = 0; i < size; ++i) {
        population[i].degree = fitness(population[i].chromosome);
    }
}

void heredity(int length, int size)
{
    int i;
    unsigned int *parent = (int *)malloc(size * 2 * sizeof(int));
    Individual *population = (Individual *)malloc(size * sizeof(Individual));
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
    printf("请输入位串长度（1 <= length <= 32）：");
    scanf("%d", &length);
    printf("请输入种群规模（size >= 1)：");
    scanf("%d", &size);
    heredity(length, size);
    return 0;
}
