#include "quick_sort.h"

static void swap(Item *a, Item *b)
{
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

static int partition(Item *arr, int left, int right)
{
    int i = left;
    int j = right;
    Item pivot = arr[left];

    while (i < j) {
        while (i < j && arr[j] >= pivot) {
            --j;
        }
        while (i < j && arr[i] <= pivot) {
            ++i;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[left], &arr[i]);

    return i;
}

static void qsort(Item *arr, int left, int right)
{
    int pivot_pos;

    if (left >= right) {
        return;
    }

    pivot_pos = partition(arr, left, right);

    qsort(arr, left, pivot_pos-1);
    qsort(arr, pivot_pos+1, right);
}

void quick_sort(Item *arr, int n)
{
    qsort(arr, 0, n-1);
}
