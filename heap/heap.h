#ifndef HEAP_H_
#define HEAP_H_

typedef int HeapItem;

typedef struct s_heap {
    int capacity;
    int size;
    HeapItem *elements;
}Heap;
typedef Heap *PriorityQueue;

PriorityQueue init(int max_elements);
PriorityQueue arr2heap(HeapItem *arr, int n);
void destroy(PriorityQueue h);
void make_empty(PriorityQueue h);
void insert(HeapItem elem, PriorityQueue h);
HeapItem delete_min(PriorityQueue h);
HeapItem find_min(PriorityQueue h);
int is_empty(PriorityQueue h);
int is_full(PriorityQueue h);

#endif
