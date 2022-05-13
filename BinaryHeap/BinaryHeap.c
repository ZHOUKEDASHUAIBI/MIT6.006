#include<stdio.h>
#include<stdlib.h>

struct Queue
{
    int capacity;
    int size;
    int *Array;
};

typedef struct Queue* PriorityQueue;

PriorityQueue Build(int *A, int lenA, int capacity);
int FindMax(PriorityQueue Q);
void Insert(PriorityQueue Q, int x);
int DeleteMax(PriorityQueue Q);
PriorityQueue Initialize(int capacity);
void PrintQueue(PriorityQueue Q);
void MaxHeapifyUp(PriorityQueue Q, int i);
void MaxHeapifyDown(PriorityQueue Q, int i);
int IsEmpty(PriorityQueue Q);
int Parent(int i);
int left(int i, int n);
int right(int i, int n);
void HeapSort(int* A, int lenA);

int main()
{
    int A[10] = {5,9,6,1,10,3,11,23,2,25};
    int i;
    /*
    int max;
    PriorityQueue Q = Build(A, 6, 15);
    PrintQueue(Q);
    Insert(Q, 11);
    PrintQueue(Q);
    max = DeleteMax(Q);
    PrintQueue(Q);
    printf("%d\n", max);
    */
    HeapSort(A, 10);
    for(i = 0; i < 10; i++) printf("%d ", A[i]);
    return 0;
}

int Parent(int i)
{
    int j = (i - 1) / 2;
    if(j < 0) return i;
    else return j;
}

int left(int i, int n)
{
    int j = 2 * i + 1;
    if(j > n) return i;
    else return j;
}

int right(int i, int n)
{
    int j = 2 * i + 2;
    if(j > n) return i;
    else return j;
}

void MaxHeapifyUp(PriorityQueue Q, int i)
{
    int j = Parent(i), temp;
    if(Q->Array[i] > Q->Array[j])
    {
        temp = Q->Array[i];
        Q->Array[i] = Q->Array[j];
        Q->Array[j] = temp;
        MaxHeapifyUp(Q, j);
    }
    return;
}

void MaxHeapifyDown(PriorityQueue Q, int i)
{
    int L = left(i, Q->size - 1);
	int R = right(i, Q->size - 1);
    int c = L, temp;
    if(Q->Array[R] > Q->Array[L]) c = R;
    if(Q->Array[i] < Q->Array[c])
    {
        temp = Q->Array[i];
        Q->Array[i] = Q->Array[c];
        Q->Array[c] = temp;
        MaxHeapifyDown(Q, c);
    }
    return;
}

int IsEmpty(PriorityQueue Q)
{
    return Q->size == 0;
}

PriorityQueue Initialize(int capacity)
{
    PriorityQueue Q = (PriorityQueue)malloc(sizeof(struct Queue));
    Q->Array = (int*)malloc(sizeof(int) * capacity);
    Q->size = 0;
    return Q;
}

PriorityQueue Build(int* A, int lenA, int capacity)
{
    PriorityQueue Q = Initialize(capacity);
    int i, begin;
    begin = lenA / 2 - 1;
    for(i = 0; i < lenA; i++)
    {
        Q->Array[i] = A[i];
        (Q->size)++;
    }
    for(i = begin; i >= 0; i--)
    {
        MaxHeapifyDown(Q, i);
    }
    return Q;
}

void PrintQueue(PriorityQueue Q)
{
    int i;
    if(!(IsEmpty(Q)))
    {
        for(i = 0; i < Q->size; i++)
        {
            printf("%d ", Q->Array[i]);
        }
    }
    printf("\n");
}

void Insert(PriorityQueue Q, int x)
{
    Q->Array[Q->size] = x;
    MaxHeapifyUp(Q, Q->size);
    Q->size++;
}

int FindMax(PriorityQueue Q)
{
    return Q->Array[0];
}

int DeleteMax(PriorityQueue Q)
{
    int maxval = Q->Array[0];
    int temp = Q->Array[(Q->size) - 1];
    Q->Array[(Q->size) - 1] = Q->Array[0];
    Q->Array[0] = temp;
    (Q->size)--;
    MaxHeapifyDown(Q, 0);
    return maxval;
}

void HeapSort(int* A, int lenA)
{
    PriorityQueue Q = Build(A, lenA, lenA);
    int i, temp;
    for(i = lenA - 1; i >= 0; i--) 
        temp = DeleteMax(Q);
    for(i = lenA - 1; i >= 0; i--) 
        A[i] = Q->Array[i];
    free(Q);
}
