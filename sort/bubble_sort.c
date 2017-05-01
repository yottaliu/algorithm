#include "bubble_sort.h"

static void swap(Item *a, Item *b)
{
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(Item *arr, int n)
{
    int i, j;
    int flag = 1;
    for (i = 0; flag && i < n-1; ++i) {
        flag = 0;
        for (j = 1; j < n-i; ++j) {
            if (arr[j] < arr[j-1]) {
                swap(&arr[j-1], &arr[j]);
                flag = 1;
            }
        }
    }
}
