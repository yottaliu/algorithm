#include "shell_sort.h"

void shell_sort(Item *arr, int n)
{
    int i, j, gap;
    Item tmp;
    for (gap = n/2; gap > 0; gap /= 2) {
        for (i = gap; i < n; ++i) {
            tmp = arr[i];
            for (j = i-gap; j >= 0 && arr[j] > tmp; j -= gap) {
                arr[j+gap] = arr[j];
            }
            arr[j+gap] = tmp;
        }
    }
}
