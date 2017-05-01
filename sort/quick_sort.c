#include "quick_sort.h"

static void swap(Item * one, Item * two)
{
    Item tmp = *one;
    *one = *two;
    *two = tmp;
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
    int pivot_index;

    if (left >= right) {
        return;
    }

    pivot_index = partition(arr, left, right);

    qsort(arr, left, pivot_index-1);
    qsort(arr, pivot_index+1, right);
}

int quick_sort(Item *arr, int n)
{
	qsort(arr, 0, n-1);
    return 1;
}
