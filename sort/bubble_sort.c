#include "bubble_sort.h"

int bubble_sort(Item *arr, int n)
{
    int i, j;
    int flag = 1;
    Item tmp;
    for (i = 0; flag && i < n-1; ++i) {
        flag = 0;
        for (j = 1; j < n-i; ++j) {
            if (arr[j] < arr[j-1]) {
                tmp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = tmp;
                flag = 1;
            }
        }
    }
    return 1;
}
