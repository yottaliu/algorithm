#ifndef HEAP_H_
#define HEAP_H_

typedef int ElementType;

typedef struct s_heap {
    int capacity;
    int size;
    ElementType *elements;
}Heap;
typedef Heap *PriorityQueue;

PriorityQueue init(int max_elements);
void build_heap(ElementType *arr, int n);
void destroy(PriorityQueue h);
void make_empty(PriorityQueue h);
void insert(ElementType elem, PriorityQueue h);
ElementType delete_min(PriorityQueue h);
ElementType find_min(PriorityQueue h);
int is_empty(PriorityQueue h);
int is_full(PriorityQueue h);

#endif
