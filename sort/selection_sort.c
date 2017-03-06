#include "selection_sort.h"

int selection_sort(ElementType *arr, int n)
{
    int i, j, min;
    ElementType tmp;
    for (i = 0; i < n-1; ++i) {
        min = i;
        for (j = i+1; j < n; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
        }
    }
    return 1;
}
