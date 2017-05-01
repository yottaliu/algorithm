#include "quick_sort.h"

void quicksort(Item *arr, int left, int right)
{
    int i, j;
    Item tmp, t;
    if (left > right) {
        return;
    }
    i = left;
    j = right;
    tmp = arr[left];
    while (i < j) {
        while (i < j && arr[j] >= tmp) {
            --j;
        }
        while (i < j && arr[i] <= tmp) {
            ++i;
        }
        if (i < j) {
            t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    arr[left] = arr[i];
    arr[i] = tmp;
    quicksort(arr, left, i-1);
    quicksort(arr, i+1, right);
}

int quick_sort(Item *arr, int n)
{
	quicksort(arr, 0, n-1);
    return 1;
}
