#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#define SIZE 100000
typedef int (*ptr)(int *, int);
typedef struct Func {
    ptr addr;
    char name[50];
    double t;
}func;

void deal(int *arr)
{
    int i, j;
    int a[SIZE];
    double s, e;
    func sort[12] =  {
        {bubble_sort, "bubble_sort"},
        {selection_sort, "selection_sort"},
        {insertion_sort, "insertion_sort"},
        {binary_insertion_sort, "binary_insertion_sort"},
        {shell_sort, "shell_sort"},
        {heap_sort, "heap_sort"},
        {merge_sort, "merge_sort"},
        {quick_sort, "quick_sort"},
        {quick2_sort, "quick2_sort"},
    };
    for (i = 0; sort[i].addr != NULL; ++i) {
        for (j = 0; j < SIZE; ++j) {
            a[j] = arr[j];
        }
        s = clock();
        sort[i].addr(a, SIZE);
        e = clock();
        sort[i].t = (e - s) / CLOCKS_PER_SEC;
        printf("%s: \t\t%lf s.\n", sort[i].name, sort[i].t);
    }
}

int main(void)
{
    int i;
    int arr[SIZE];

    srand((unsigned)time(0));
    for (i = 0; i < SIZE; ++i) {
        arr[i] = rand();
    }
    printf("Random input:\n");
    deal(arr);
    printf("\n");

    for (i = 0; i < SIZE; ++i) {
        arr[i] = i;
    }
    printf("Input is presorted:\n");
    deal(arr);
    printf("\n");

    for (i = 0; i < SIZE; ++i) {
        arr[i] = SIZE - 1 - i;
    }
    printf("Input is in reverse order:\n");
    deal(arr);
    printf("\n");

    for (i = 0; i < SIZE; ++i) {
        arr[i] = 0;
    }
    printf("All inputs are equal:\n");
    deal(arr);
    printf("\n");

    return 0;
}
