/* Use selection sort algorithm to sort a sequence in ascending orders. */

#include <stdio.h>
#include <stdlib.h>

void SelectSort(int A[], int N);
void PrintArray(int A[], int N);
void Swap(int *A, int *B);

int main() {
    int N, *A;

    scanf("%d", &N);

    A = (int *)malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++) {
        scanf("%d,", &A[i]);
    }

    SelectSort(A, N);

    free(A);

    return 0;
}

void SelectSort(int A[], int N) {
    int i, j, min_idx;

    for (i = 0; i < N - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < N; j++) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }
        Swap(&A[i], &A[min_idx]);
        PrintArray(A, N);
    }
}

void PrintArray(int A[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d,", A[i]);
    }
    putchar('\n');
}

void Swap(int *A, int *B) {
    int tmp;

    tmp = *A;
    *A = *B;
    *B = tmp;
}