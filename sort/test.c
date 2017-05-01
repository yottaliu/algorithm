#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#define SIZE 11
#define sort quick_sort

void show(Item *arr)
{
    int i;
    for (i = 0; i < SIZE; ++i) {
        printf("%4d", arr[i]);
    }
}

int main(void)
{
    int i;
    Item arr[SIZE];

    srand((unsigned)time(0));
    for (i = 0; i < SIZE; ++i) {
        arr[i] = rand() % 100;
    }
    printf("Random input:\n");
    sort(arr, SIZE);
    show(arr);
    putchar('\n');

    for (i = 0; i < SIZE; ++i) {
        arr[i] = i;
    }
    printf("Input is presorted:\n");
    sort(arr, SIZE);
    show(arr);
    putchar('\n');

    for (i = 0; i < SIZE; ++i) {
        arr[i] = SIZE - 1 - i;
    }
    printf("Input is in reverse order:\n");
    sort(arr, SIZE);
    show(arr);
    putchar('\n');

    for (i = 0; i < SIZE; ++i) {
        arr[i] = 0;
    }
    printf("All inputs are equal:\n");
    sort(arr, SIZE);
    show(arr);
    putchar('\n');

    return 0;
}
