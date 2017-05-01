#include <stdlib.h>
#include "heap.h"

PriorityQueue init(int max_elements)
{
    PriorityQueue h;

    h = (PriorityQueue)malloc(sizeof(Heap));
    if (h == NULL) {
        return NULL;
    }

    h->elements = (HeapItem *)malloc(max_elements * sizeof(HeapItem));
    if (h->elements == NULL) {
        free(h);
        return NULL;
    }

    h->capacity = max_elements;
    h->size = 0;

    return h;
}

void make_empty(PriorityQueue h)
{
    h->size = 0;
}

#define parent(i) (((i) - 1) / 2)
static void percolate_up(int i, HeapItem *arr)
{
    HeapItem tmp;
    for (tmp = arr[i]; i > 0 && arr[parent(i)] > tmp; i = parent(i)) {
        arr[i] = arr[parent(i)];
    }
    arr[i] = tmp;
}

void insert(HeapItem elem, PriorityQueue h)
{
    h->elements[h->size++] = elem;
    percolate_up(h->size - 1, h->elements);
}

#define left_child(i)  (2 * (i) + 1)
static void percolate_down(int i, HeapItem *arr, int n)
{
    int child;
    HeapItem tmp;
    for(tmp = arr[i]; left_child(i) < n; i = child) {
        child = left_child(i);
        if(child != n-1 && arr[child+1] < arr[child]) {
            child++;
        }
        if(tmp > arr[child]) {
            arr[i] = arr[child];
        } else {
            break;
        }
    }
    arr[i] = tmp;
}

PriorityQueue arr2heap(HeapItem *arr, int n)
{
    int i;
    PriorityQueue h;

    h = (PriorityQueue)malloc(sizeof(Heap));
    if (h == NULL) {
        return NULL;
    }

    for(i = n/2; i >= 0; --i) {
        percolate_down(i, arr, n);
    }

    h->elements = arr;

    h->capacity = n;
    h->size = n;

    return h;
}

HeapItem delete_min(PriorityQueue h)
{
    HeapItem min;

    min = h->elements[0];
    h->elements[0] = h->elements[h->size--];
    percolate_down(0, h->elements, h->size);

    return min;
}

HeapItem find_min(PriorityQueue h)
{
    return h->elements[0];
}

int is_empty(PriorityQueue h)
{
    return h->size == 0;
}

int is_full(PriorityQueue h)
{
    return h->size == h->capacity;
}

void destroy(PriorityQueue h)
{
    free(h->elements);
    free(h);
}
