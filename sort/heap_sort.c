#include "heap_sort.h"

static void swap(Item *a, Item *b)
{
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

#define left_child(i)  (2 * (i) + 1)
static void percolate_down(int i, Item *arr, int n)
{
    int child;
    Item tmp;
    for(tmp = arr[i]; left_child(i) < n; i = child) {
        child = left_child(i);
        if(child != n-1 && arr[child+1] > arr[child]) {
            child++;
        }
        if(tmp < arr[child]) {
            arr[i] = arr[child];
        } else {
            break;
        }
    }
    arr[i] = tmp;
}

void heap_sort(Item *arr, int n)
{
    int i;
    for(i = n/2; i >= 0; --i) {
        percolate_down(i, arr, n);
    }
    for(i = n-1; i > 0; --i) {
        swap(&arr[0], &arr[i]);
        percolate_down(0, arr, i);
    }
}
