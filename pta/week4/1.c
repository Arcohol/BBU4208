/* We can build Binary Heaps by two methods, the first is to insert items one by one from the input;
 * the second is to build A random binary tree all together from the input at first and then adjust
 * the tree to A binary heap. (As described in book P.140)

 * Give A sequence of distinct integer to build two binary heaps in those two ways, and output the
 * nodes on level order of each tree. */

#include <stdio.h>
#include <stdlib.h>

#define INFINITY 0x3f3f3f3f

typedef int ElementType;

typedef struct Heap {
    int size, capacity;
    ElementType *elements;
} Heap;
typedef Heap *PriorityQueue;

PriorityQueue CreateQueue(int N);
void Insert(ElementType X, PriorityQueue H);
void Swap(int *A, int *B);
void PercolateDown(int i, PriorityQueue H);
void PrintHeap(PriorityQueue H);
void DisposeQueue(PriorityQueue H);

int main() {
    PriorityQueue A, B;
    int N, X;

    scanf("%d", &N);

    A = CreateQueue(N);
    B = CreateQueue(N);

    for (int i = 0; i < N; i++) {
        scanf("%d,", &X);

        Insert(X, A);
        B->elements[++B->size] = X;
    }
    for (int i = B->size / 2; i >= 0; i--) {
        PercolateDown(i, B);
    }

    PrintHeap(A);
    PrintHeap(B);

    DisposeQueue(A);
    DisposeQueue(B);

    return 0;
}

PriorityQueue CreateQueue(int N) {
    PriorityQueue H;

    H = (PriorityQueue)malloc(sizeof(Heap));
    H->elements = (ElementType *)malloc((N + 2) * sizeof(ElementType));
    H->capacity = N;
    H->size = 0;
    H->elements[0] = -1;
    for (int i = 1; i < N + 2; i++) {
        H->elements[i] = INFINITY;
    }

    return H;
}

void Insert(ElementType X, PriorityQueue H) {
    int i;

    for (i = ++H->size; X < H->elements[i / 2]; i /= 2) {
        H->elements[i] = H->elements[i / 2];
    }
    H->elements[i] = X;
}

void Swap(int *A, int *B) {
    int tmp;

    tmp = *A;
    *A = *B;
    *B = tmp;
}

void PercolateDown(int i, PriorityQueue H) {
    int target;

    target = H->elements[i * 2] < H->elements[i * 2 + 1] ? i * 2 : i * 2 + 1;
    if (H->elements[i] > H->elements[target]) {
        Swap(&H->elements[i], &H->elements[target]);
        if (target <= H->size / 2) {
            PercolateDown(target, H);
        }
    }
}

void PrintHeap(PriorityQueue H) {
    for (int i = 1; i <= H->size; i++) {
        printf("%d", H->elements[i]);
        if (i == H->size) {
            putchar('\n');
        } else {
            putchar(',');
        }
    }
}

void DisposeQueue(PriorityQueue H) {
    free(H->elements);
    free(H);
}