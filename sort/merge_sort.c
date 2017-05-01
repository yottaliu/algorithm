#include <stdlib.h>
#include "merge_sort.h"

static void merge(Item *arr, int left, int center, int right, Item *tmp_arr)
{
    int left_pos = left;
    int left_end = center;
    int right_pos = left_end+1;
    int right_end = right;
    int count_item = 0;
    while (left_pos <= left_end && right_pos <= right_end) {
        if (arr[left_pos] <= arr[right_pos]) {
            tmp_arr[count_item++] = arr[left_pos++];
        } else {
            tmp_arr[count_item++] = arr[right_pos++];
        }
    }
    while (left_pos <= left_end) {
        tmp_arr[count_item++] = arr[left_pos++];
    }
    while (right_pos <= right_end) {
        tmp_arr[count_item++] = arr[right_pos++];
    }
    for (int i = 0; i < count_item; ++i) {
        arr[left+i] = tmp_arr[i];
    }
}

static void msort(Item *arr, int left, int right, Item *tmp_arr)
{
    int center;
    if (left < right) {
        center = (left + right) / 2;
        msort(arr, left, center, tmp_arr);
        msort(arr, center+1, right, tmp_arr);
        merge(arr, left, center, right, tmp_arr);
    }
}

void merge_sort(Item *arr, int n)
{
    Item *tmp_arr = (Item *) malloc(n * sizeof(Item));
    msort(arr, 0, n-1, tmp_arr);
    free(tmp_arr);
}
