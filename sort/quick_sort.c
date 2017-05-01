#include "quick_sort.h"

static int partition(Item *arr, int left, int right)
{
    int i, j;
    Item tmp, t;

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

    return i;
}

static void qsort(Item *arr, int left, int right)
{
    int pivot;
    if (left > right) {
        return;
    }

    pivot = partition(arr, left, right);
    qsort(arr, left, pivot-1);
    qsort(arr, pivot+1, right);
}

int quick_sort(Item *arr, int n)
{
	qsort(arr, 0, n-1);
    return 1;
}
