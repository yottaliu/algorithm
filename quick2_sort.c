typedef int ElementType;

void swap(ElementType * one, ElementType * two)
{
    ElementType temp;

    temp = *one;
    *one = *two;
    *two = temp;
}

ElementType Median3(ElementType A[], int left, int right)
{
    int center;

    center = (left + right) / 2;
    if (A[left] > A[center]) {
        swap(&A[left], &A[center]);
    }
    if (A[left] > A[right]) {
        swap(&A[left], &A[right]);
    }
    if (A[center] > A[right]) {
        swap(&A[center], &A[right]);
    }
    swap(&A[center], &A[right-1]);

    return A[right-1];
}

#define cutoff (3)

void Qsort(ElementType A[], int left, int right)
{
    int i, j;
    ElementType pivot;

    if (left + cutoff <= right) {
        pivot = Median3(A, left, right);
        i = left;
        j = right - 1;
        while (1)
        {
            while (A[++i] < pivot) {
                continue;
            }
            while (A[--j] > pivot) {
                continue;
            }
            if (i < j) {
                swap(&A[i], &A[j]);
            } else {
                break;
            }
        }
        swap(&A[i], &A[right-1]);

        Qsort(A, left, i-1);
        Qsort(A, i+1, right);
    } else {
        InsertionSort(A+left, right-left+1);
    }
}

void QuickSort(ElementType A[], int n)
{
    Qsort(A, 0, n-1);
}
