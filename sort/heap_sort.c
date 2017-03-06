#include "heap_sort.h"

static void swap(ElementType * one, ElementType * two)
{
    ElementType tmp;
    tmp = *one;
    *one = *two;
    *two = tmp;
}

#define left_child(i)  (2 * (i) + 1)
void percolate_down(int i, ElementType *arr, int n)
{
    int child;
    ElementType tmp;
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

int heap_sort(ElementType arr[], int n)
{
    int i;
    for(i = n/2; i >= 0; --i) {
        percolate_down(i, arr, n);
    }
    for(i = n-1; i > 0; --i) {
        swap(&arr[0], &arr[i]);
        percolate_down(0, arr, i);
    }
    return 1;
}
