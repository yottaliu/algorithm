#include "selection_sort.h"

static void swap(Item *a, Item *b)
{
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

void selection_sort(Item *arr, int n)
{
    int i, j, min;
    for (i = 0; i < n-1; ++i) {
        min = i;
        for (j = i+1; j < n; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(&arr[min], &arr[i]);
        }
    }
}
