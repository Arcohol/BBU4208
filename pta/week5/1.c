/* Implement the insertion sort algorithm in descending order. */

#include <stdio.h>
#include <stdlib.h>

void InsertionSort(int A[], int N);
void PrintArray(int A[], int N);

int main() {
    int N, *A;

    scanf("%d", &N);

    A = (int *)malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++) {
        scanf("%d,", &A[i]);
    }

    InsertionSort(A, N);

    free(A);

    return 0;
}

void InsertionSort(int A[], int N) {
    int tmp, i, j;

    for (i = 1; i < N; i++) {
        tmp = A[i];
        for (j = i; j > 0 && A[j - 1] > tmp; j--) {
            A[j] = A[j - 1];
        }
        A[j] = tmp;
        PrintArray(A, N);
    }
}

void PrintArray(int A[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d,", A[i]);
    }
    putchar('\n');
}