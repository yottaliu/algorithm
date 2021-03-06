#include "binary_insertion_sort.h"

void binary_insertion_sort(Item *arr, int n)
{
    int i, j, low, high, center;
    Item tmp;
    for (i = 1; i < n; ++i) {
        low = 0;
        high = i - 1;
        tmp = arr[i];
        while (low <= high) {
            center = (low + high) / 2;
            if (tmp < arr[center]) {
                high = center - 1;
            } else {
                low = center + 1;
            }
        }
        for (j = i; j > center; --j) {
            arr[j] = arr[j-1];
        }
        arr[low] = tmp;
    }
}
