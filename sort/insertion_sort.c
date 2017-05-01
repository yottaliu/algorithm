#include "insertion_sort.h"

void insertion_sort(Item *arr, int n)
{
    int i, j;
    Item tmp;
    for (i = 1; i < n; ++i) {
        tmp = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > tmp; --j) {
            arr[j+1] = arr[j];
        }
        arr[j+1] = tmp;
    }
}
